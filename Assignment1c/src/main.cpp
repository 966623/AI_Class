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
#include "Phong.hpp"
#include "Light.hpp"
#include "Basiclight.hpp"
#include "Spotlight.hpp"
#include "Polygon.hpp"
#include "Triangle.hpp"
#include "Vertex.hpp"
#include "UvCoord.hpp"
#include "Normal.hpp"

using namespace std;

void readFile(char* fileName, ifstream& stream);
ImgSettings parseFile(ifstream& inputFile);
void makeImage(ImgSettings settings);
int makeObjects(ImgSettings& settings, Camera &c, Image &i, vector<Object*> &obj, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uvs, vector<Polygon*> &poly, vector<Material*> &mtl, vector<Light*> &lt);
void render(Image &img, Camera &cam, vector<Object*> &obj, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uvs, vector<Polygon*> &poly, vector<Material*> &mtl, vector<Light*> &lt, ofstream &file);
void errorExit(void);
ofstream outputFile;

int main(int argc, char **argv)
{
    //
    atexit(errorExit);
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
                token = strtok (NULL, " \t");
            }
            newSettings.setData(name, propList);
            
        }

    } while(inputFile.tellg() != -1);
    return newSettings;
}


int makeObjects(ImgSettings& settings, Camera &c, Image &i, 
        vector<Object*> &obj, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uvs, vector<Polygon*> &poly, 
        vector<Material*> &mtl, vector<Light*> &lt){

    //IMAGE -----
    cout << "Setting Up Image...\n";
    // Image size
    vector<string> imsize = settings.getData("imsize");

    // check validity
    if(imsize.size() != 2){
        cout << "ERROR: IMAGE SIZE WITH 2 DIMENSIONS MUST BE PROVIDED\n";
        exit(EXIT_FAILURE);
    }

    float width = stof(imsize[0]);
    float height = stof(imsize[1]);
    

    if(width < 0 || height < 0){
        cout << "ERROR: IMAGE DIMENSIONS MUST BE POSITIVE\n";
        exit(EXIT_FAILURE);
    }

    float ratio = width / height;

    //background color
    cout << "Image size : " << width << " x " << height << "\n";
    vector<string> bkgcolor = settings.getData("bkgcolor");

    // create new Image object;
    Image newImg = Image(width, height, bkgcolor);
    i = newImg;
    // ----------------

    //CAMERA -----
    cout << "Setting Up Camera...\n";
    vector<string> eyeLoc = settings.getData("eye");
    vector<string> updir = settings.getData("updir");
    vector<string> viewdir = settings.getData("viewdir");
    vector<string> fov = settings.getData("fovv");

    // Create new camera object
    Camera mainCam = Camera(ratio, eyeLoc, updir, viewdir, fov);

    if(settings.seek("parallel") != -1){
        cout << "Camera uses parallel projection\n";
        mainCam.setPerspective(false);
    }
    
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
            newMaterial = new Material(mtlData);
            mtl.push_back(newMaterial);
        }
        else if(name == "sphere"){ // Set up new sphere if sphere found
            cout << "Making Sphere\n";
            Sphere *newSphere = new Sphere(get<1>(line), newMaterial);
            obj.push_back(newSphere);
        }
        else if(name == "ellipsoid"){ // Set up new ellipsoid if ellipsoid found
            cout << "Making Ellipsoid\n";
            Ellipsoid *newEllipsoid = new Ellipsoid(get<1>(line), newMaterial);
            obj.push_back(newEllipsoid);
        }
    }
    // --------------

    //Vertices ----------
    cout << "Making Polygons\n";
    settings.seekStart();

    while(get<0>(line = settings.next()) != "eof"){
        string name = get<0>(line);
        if(name == "v"){
            cout << "Making Vertex\n";
            vector<string> vertData = get<1>(settings.getCurrent());
            Vertex* newVert = new Vertex(vertData);
            vert.push_back(newVert);
        }
        if(name == "vn"){
            cout << "Making Vertex Normal\n";
            vector<string> normData = get<1>(settings.getCurrent());
            Normal* newNorm = new Normal(normData);
            norm.push_back(newNorm);
        }
        if(name == "vt"){
            cout << "Making UV Coordinate\n";
            vector<string> uvData = get<1>(settings.getCurrent());
            UvCoord* newUv = new UvCoord(uvData);
            uvs.push_back(newUv);
        }
        if(name == "f"){
            cout << "Making Polygon\n";
            vector<string> polyData = get<1>(settings.getCurrent());
            Polygon* newPoly = new Polygon(polyData, vert, norm, uvs, mtl[0]);
            poly.push_back(newPoly);
            obj.push_back(newPoly);
        }
    }
    // ----------------

    //Lights ----------
    cout << "Making Lights\n";
    settings.seekStart();

    while(get<0>(line = settings.next()) != "eof"){
        string name = get<0>(line);
        if(name == "light"){
            cout << "Making Point/Directional Light\n";
            vector<string> ltData = get<1>(settings.getCurrent());
            Light* newLight = new Basiclight(ltData);
            lt.push_back(newLight);
        }

        else if(name == "spotlight"){
            cout << "Making Spotlight\n";
            vector<string> ltData = get<1>(settings.getCurrent());
            Light* newLight = new Spotlight(ltData);
            lt.push_back(newLight);
        }
    }
    // ----------------


    return 0;

}
void makeImage(ImgSettings settings){
    
    
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
    vector<Light*> lights;
    vector<Vertex*> vertices;
    vector<Polygon*> polygons;
    vector<Normal*> normals;
    vector<UvCoord*> uvs;
    makeObjects(settings, cam, img, objects, vertices, normals, uvs, polygons, materials, lights);

    // Write image size to file
    outputFile << img.width << " " << img.height << "\n";

    // Max color value
    outputFile << maxColor << "\n";
    
    render(img, cam, objects, vertices, normals, uvs, polygons, materials, lights, outputFile);

    outputFile.close();
    cout << "Image successfully created\n";
}

void render(Image &img, Camera &cam, 
        vector<Object*> &obj, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uvs, vector<Polygon*> &poly, 
        vector<Material*> &mtl, vector<Light*> &lt, ofstream &file){

    cout << "Rendering...\n";
    if(obj.size() == 0){
        cout << "ERROR: No objects to render\n";
        exit(EXIT_FAILURE);
    }

    float maxColor = 255;

    Phong phongRender = Phong();

    // Calculate pixels
    for(int y = 0; y < img.height; y++){
        for(int x = 0; x < img.width; x++){
            
            //Define ray
            tuple<Vec3, Vec3> rayInfo = cam.getPixelRay(img.width, img.height, x, y);
            Vec3 rayDir = get<1>(rayInfo);
            Vec3 rayStart = get<0>(rayInfo);

            float distance = -1;
            Material* material = mtl[0];
            Object* closestObject = obj[0];

            // Check intersection with every object
            for(int i = 0; i < obj.size(); i++){
                float dist = obj[i]->getIntersect(rayStart, rayDir);
                if(distance < 0 || (dist < distance && dist >= 0)){
                    distance = dist;
                    material = obj[i]->material;
                    closestObject = obj[i];
                }
            }
            
            // Choose nearest intersection and write color to image. If no intersection write background color
            if (distance < 0){
                img.set(x, y, img.bkg);
            }
            else{
                Material *m = material;
                Vec3 intersect = rayStart + (distance*rayDir);
                img.set(x, y, phongRender.calc(intersect, &cam, closestObject, lt, obj));
                //img.set(x, y, m->color);
            }
        }
    }

    img.write(file);


}

void readFile(char* fileName, ifstream& stream){
    cout << "Reading image info from " << fileName << "\n";
    stream.open (fileName, ifstream::in);
    if(!stream){
        cout << "File not found.\n";
    }
}

void errorExit(void){
    outputFile.close();

}