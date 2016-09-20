#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vec3.hpp"
#include "ImgSettings.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Material.hpp"
#include "Ellipsoid.hpp"

using namespace std;

void readFile(char* fileName, ifstream& stream);
ImgSettings parseFile(ifstream& inputFile);
void makeImage(ImgSettings settings);
int makeObjects(ImgSettings& settings, Camera &c, Image &i, vector<Object*> &obj, vector<Material*> &mtl);
void render(Image &img, Camera &cam, vector<Object*> &obj, vector<Material*> &mtl, ofstream &file);

int main(int argc, char **argv)
{
    // Check to see that there is an input file
    if(argc != 2){
        cout << "Invalid nubmer of arguments\n";
        return 0;
    }

    // Read file into a stream
    ifstream inputFile;
    readFile(argv[1], inputFile);

    // Parse file into image settings
    ImgSettings settings = parseFile(inputFile);
    cout << settings.to_str();
    inputFile.close();

    // Output image
    makeImage(settings);
    
    return 0;
}

ImgSettings parseFile(ifstream& inputFile){
    string line;
    ImgSettings newSettings;
    cout << "Parsing File...\n";
    //Iterate over eachline
    do{
        getline (inputFile, line);
        vector<string> propList;
        if(line.size() == 0){
            //do nothing, empty line
        }
        else if(line[0] == '#'){
            // Comment found, do nothing
        }
        else{ // settings found, add a new setting
            char lineChar[line.size()+1];
            strcpy(lineChar, line.c_str());
            char * token;
            char * name;
            name = strtok (lineChar," \t");
            token = strtok (NULL," \t");

            //Put properties on this line into a vector
            while (token != NULL)
            {
                propList.push_back(token);
                token = strtok (NULL, " ");
            }
            newSettings.setData(name, propList);
            
        }

    } while(inputFile.tellg() != -1);
    return newSettings;
}


int makeObjects(ImgSettings& settings, Camera &c, Image &i, vector<Object*> &obj, vector<Material*> &mtl){
    //IMAGE -----
    cout << "Setting Up Image...\n";
    // Image size
    vector<string> imsize = settings.getData("imsize");

    // check validity
    if(imsize.size() != 2){
        cout << "ERROR: IMAGE SIZE WITH 2 DIMENSIONS MUST BE PROVIDED\n";
        return -1;
    }

    float width = stof(imsize[0]);
    float height = stof(imsize[1]);
    

    if(width < 0 || height < 0){
        cout << "ERROR: IMAGE DIMENSIONS MUST BE POSITIVE\n";
        return -1;
    }

    float ratio = width / height;

    //background color
    cout << "Image size : " << width << " x " << height << "\n";
    vector<string> bkgcolor = settings.getData("bkgcolor");
    Vec3 bkgcolorVec;
    if(bkgcolor.size() != 3){
        bkgcolorVec = Vec3(1, 1, 1);
        cout << "Background color not specified, background color defaulted to white.\n";
    }
    else{
        bkgcolorVec = Vec3(stof(bkgcolor[0]), stof(bkgcolor[1]), stof(bkgcolor[2]));
    }    

    // create new Image object;
    Image newImg = Image(width, height, bkgcolorVec);
    i = newImg;
    // ----------------

    //CAMERA -----
    cout << "Setting Up Camera...\n";
    // Eye location
    vector<string> eyeLoc = settings.getData("eye");
    // check validity
    if(eyeLoc.size() != 3){
        cout << "ERROR: VALID X Y Z CAMERA COORDINATES REQUIRED\n";
        return -1;
    }
    Vec3 eyeLocVec = Vec3(stof(eyeLoc[0]), stof(eyeLoc[1]), stof(eyeLoc[2]));

    // Up direction
    vector<string> updir = settings.getData("updir");
    if(updir.size() != 3){
        cout << "ERROR: VALID UP DIRECTION VECTOR REQUIRED\n";
        return -1;
    }
    if(stof(updir[0]) == 0 && stof(updir[1]) == 0 && stof(updir[2]) == 0){
        cout << "ERROR: UP DIRECTION VECTOR MUST HAVE NON ZERO LENGTH\n";
        return -1;
    }
    Vec3 updirVec = Vec3(stof(updir[0]), stof(updir[1]), stof(updir[2]));

    // View direction
    vector<string> viewdir = settings.getData("viewdir");
    if(viewdir.size() != 3){
        cout << "ERROR: VALID VIEW DIRECTION VECTOR REQUIRED\n";
        return -1;
    }
    if(stof(viewdir[0]) == 0 && stof(viewdir[1]) == 0 && stof(viewdir[2]) == 0){
        cout << "ERROR: VIEW DIRECTION VECTOR MUST HAVE NON ZERO LENGTH\n";
        return -1;
    }
    Vec3 viewdirVec = Vec3(stof(viewdir[0]), stof(viewdir[1]), stof(viewdir[2]));


    // Vertical Field of View
    vector<string> fov = settings.getData("fovv");
    if(fov.size() < 1){
        cout << "ERROR: VERTICAL FIELD OF VIEW REQUIRED\n";
        return -1;
    }
    if (stof(fov[0]) >= 180){
        cout << "ERROR: FOV MUST BE LESS THAN 180 DEGREES\n";
    }
    float fovFloat = stof(fov[0]);

    if((viewdirVec * updirVec).magnitude() <= 0){
        cout << "ERROR: UP DIRECTION AND VIEW DIRECTION CANNOT BE PARALLEL\n";
        return -1;
    }

    // Create new camera object
    Camera mainCam = Camera(eyeLocVec, updirVec, viewdirVec, fovFloat, ratio);
    c = mainCam;
    // -----------

    // Objects ------
    cout << "Setting up objects...\n";

    // find first material
    cout << "Making Material\n";
    settings.seekStart();
    settings.seek("mtlcolor");
    int mtlIndex = 0;
    vector<string> mtlData = get<1>(settings.getCurrent());
    //check validity
    if(mtlData.size() != 3){
        cout << "ERROR: AT LEAST ONE R G B MATERIAL COLOR REQUIRED\n";
        return -1;
    }
    Material *newMaterial = new Material(mtlData);
    mtl.push_back(newMaterial);

    // Add objects/materials to list of objects/materials
    tuple<string, vector<string>> line;
    while(get<0>(line = settings.next()) != "eof"){
        string name = get<0>(line);
        if(name == "mtlcolor"){ // Set new material if new material found
            cout << "Making Material\n";
            mtlIndex++;
            mtlData = get<1>(settings.getCurrent());
            if(mtlData.size() != 3){
                cout << "ERROR: MATERIAL #" << mtlIndex + 1 << " IS INVALID\n";
                return -1;
            }
            newMaterial = new Material(mtlData);
            mtl.push_back(newMaterial);
        }
        else if(name == "sphere"){ // Set up new sphere if sphere found
            cout << "Making Sphere\n";
            if(get<1>(line).size() != 4){
                cout << "ERROR: INVALID SPHERE\n";
                return -1;
            }
            Sphere *newSphere = new Sphere(get<1>(line), mtlIndex);
            obj.push_back(newSphere);
        }
        else if(name == "ellipsoid"){ // Set up new sphere if sphere found
            cout << "Making Ellipsoid\n";
            if(get<1>(line).size() != 6){
                cout << "ERROR: INVALID ELLIPSOID\n";
                return -1;
            }
            Ellipsoid *newEllipsoid = new Ellipsoid(get<1>(line), mtlIndex);
            obj.push_back(newEllipsoid);
        }
    }
    // --------------


    return 0;

}
void makeImage(ImgSettings settings){
    ofstream outputFile;
    
    // Core image info
    outputFile.open ("output.ppm");
    outputFile << "P3\n";
    outputFile << "# My Image Maker\n";
    float maxColor = 255;

    // instantiate objects
    Image img;
    Camera cam;
    vector<Object*> objects;
    vector<Material*> materials;
    if(makeObjects(settings, cam, img, objects, materials) == -1){
        outputFile.close();
        remove("output.ppm");
        cout << "Error processing input, exiting...\n";
        return;
    }

    // Write image size to file
    outputFile << img.width << " " << img.height << "\n";

    // Max color value
    outputFile << maxColor << "\n";
    
    render(img, cam, objects, materials, outputFile);

    outputFile.close();
    cout << "Image successfully created\n";
}

void render(Image &img, Camera &cam, vector<Object*> &obj, vector<Material*> &mtl, ofstream &file){
    cout << obj.size() << "\n";
    float maxColor = 255;

    // Calculate pixel offset
    Vec3 offsetV = (cam.ll - cam.ul)/(img.height - 1);
    Vec3 offsetH = (cam.ur - cam.ul)/(img.width - 1);

    for(int y = 0; y < img.height; y++){
        for(int x = 0; x < img.width; x++){
            
            //Define ray
            Vec3 rayEnd = cam.ul + (y*offsetV) + (x*offsetH);
            Vec3 rayDir = rayEnd - cam.pos;
            rayDir.normalize();
            float distance = -1;
            int material = -1;

            // Check intersection with every object
            for(int i = 0; i < obj.size(); i++){
                float dist = obj[i]->getIntersect(cam.pos, rayDir);
                if(distance == -1 || (dist < distance && dist != -1)){
                    distance = dist;
                    material = obj[i]->material;
                }
            }
            // Choose nearest intersection and write color to image. If no intersection write background color
            if (distance < 0){
                file << (int)(img.bkg.x * maxColor) << " " << (int)(img.bkg.y * maxColor) << " "  << (int)(img.bkg.z * maxColor )<< "\n";
            }
            else{
                Material *m = mtl[material];
                file << (int)(m->color.x * maxColor)<< " " << (int)(m->color.y * maxColor) << " "  << (int)(m->color.z * maxColor) << "\n";
            }
        }
    }
}

void readFile(char* fileName, ifstream& stream){
    cout << "Reading image info from " << fileName << "\n";
    stream.open (fileName, ifstream::in);
    if(!stream){
        cout << "File not found.\n";
    }
}