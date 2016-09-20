#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <stdio.h>
#include <string.h>

#include "ImgSettings.hpp"

using namespace std;

void readFile(char* fileName, ifstream& stream);
ImgSettings parseFile(ifstream& inputFile);
void makeImage(ImgSettings settings);

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

    //Iterate over eachline
    getline (inputFile, line);
    while(inputFile.tellg() != -1){
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
            name = strtok (lineChar," ");
            token = strtok (NULL," ");

            //Put properties on this line into a vector
            while (token != NULL)
            {
                propList.push_back(token);
                token = strtok (NULL, " ");
            }
            newSettings.setData(name, propList);
            
        }
        getline (inputFile, line);

    }
    return newSettings;
}

void makeImage(ImgSettings settings){
    ofstream outputFile;
    
    // Core image info
    outputFile.open ("output.ppm");
    outputFile << "P3\n";
    outputFile << "# My Image Maker\n";

    // Image size
    vector<string> imsize = settings.getData("imsize");
    // check validity
    if(imsize.size() != 2){
        cout << "ERROR: IMAGE SIZE WITH 2 DIMENSIONS MUST BE PROVIDED\n";
        outputFile.close();
        remove("output.ppm");
        return;
    }
    int width = atoi(imsize[0].c_str());
    int height = atoi(imsize[1].c_str());
    int imageSize = width * height;
    if(width < 0 || height < 0){
        cout << "ERROR: IMAGE DIMENSIONS MUST BE POSITIVE\n";
        outputFile.close();
        remove("output.ppm");
        return;
    }
    // Write size to file
    outputFile << width << " " << height << "\n";
    

    // Max color value
    outputFile << "255\n";

    // make an r g b striped image
    for(int i = 0; i < imageSize; i++){
        if (i%3 == 0){
            outputFile << "255 0 0\n";
        }
        else if (i%3 == 1){
            outputFile << "0 255 0\n";
        }
        else{
            outputFile << "0 0 255\n";
        }
    }
    outputFile.close();
    cout << "Image successfully created\n";
}

void readFile(char* fileName, ifstream& stream){
    cout << "Reading image info from " << fileName << "\n";
    stream.open (fileName, ifstream::in);
    if(!stream){
        cout << "File not found.\n";
    }
}