#ifndef Texture_HPP
#define Texture_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <algorithm> 
#include <fstream>
#include "Vec3.hpp"
#include "UvCoord.hpp"
#include "Vertex.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Texture {
	public:

		int height = -1;
		int width = -1;
		int maxColor = 255;
		vector<vector<Vec3>> pixels;
		Vec3 bkg;
		Texture (){

		}

		Texture (vector<string> &data){
			if(data.size() != 1){
				cout << "ERROR: Invalid texture, must have 1 filename\n";
				exit(EXIT_FAILURE);
			}
			string fileName = data[0];
			ifstream inputFile;
			cout << "Texture name: " << fileName << "\n";
    		inputFile.open (fileName, ifstream::in);
    		if(!inputFile){
		        cout << "Texture file not found.\n";
		        exit(EXIT_FAILURE);
		    }

		    string line;
		    int x = 0;
		    int y = 0;
		    do{
		    	getline(inputFile, line);
		    	vector<string> propList;
		    	if(line.size() == 0){
		    		// do nothing, empty line
		    	}
		    	else{
		    		//Split line by spaces
		    		char lineChar[line.size()+1];
		            strcpy(lineChar, line.c_str());
		            char * token;
		            char * name;
		            token = strtok (lineChar," \t");
		            propList.push_back(token);
		            token = strtok (NULL," \t");

		            while (token != NULL)
		            {
		                propList.push_back(token);
		                token = strtok (NULL, " \t");
		            }

		            //store values

		            //Header
		            if(propList[0] == "P3"){
		            	width = stoi(propList[1]);
		            	height = stoi(propList[2]);
		            	maxColor = stoi(propList[3]);
		            	cout << width << " " << height << "\n";
		            	pixels.resize(height);
		            	for(int i = 0; i < height; i++){
		            		pixels[i].resize(width);
		            	}
		            }

		            else{
		            	if(width < 1 || height < 1){
		            		cout << "ERROR: improper texture header file not found.\n";
		        			exit(EXIT_FAILURE);
		            	}
		            	pixels[y][x] = Vec3(stof(propList[0])/maxColor, stof(propList[1])/maxColor, stof(propList[2])/maxColor);

		            	x++;
		            	if(x >= width){
		            		x = 0;
		            		y++;
		            	}
		            }

		    	}

		    } while (inputFile.tellg() != -1);


		}

		Vec3 getColor(Vec3 &newCoord){
			if(newCoord.x > 1){
				newCoord.x = 1;
			}
			if(newCoord.y > 1){
				newCoord.y = 1;
			}
			if(newCoord.x < 0){
				newCoord.x = 0;
			}
			if(newCoord.y < 0){
				newCoord.y = 0;
			}

			float x = newCoord.x*(width-1);
			float y = newCoord.y*(height-1);
			int i = floor(x);
			int j = floor(y);
			float a = x - i;
			float b = y - j;
			Vec3 color = (1 - a) * (1 - b) * pixels[j][i] + 
				(a) * (1 - b) * pixels[j][i+1] + 
				(1 - a) * (b) * pixels[j+1][i] + 
				(a) * (b) * pixels[j+1][i+1];
			return color;
		}

		

	private:
		
}; // end SomeClass

#endif
