#ifndef Polygon_HPP
#define Polygon_HPP

#include "Object.hpp"
#include "Material.hpp"
#include "Vertex.hpp"
#include "Normal.hpp"
#include "UvCoord.hpp"
#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vec3.hpp"


using namespace std;

class Polygon: public Object {
	public:

		Vec3 normal;
		vector<Vertex*> vertices;
		vector<Normal*> normals;
		vector<UvCoord*> uvs;
		float area;

		Polygon (){

		}

		Polygon (vector<string> &data, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uv, Material* m){
			for(int i = 0; i < 3; i++){
				vector<string> splitData;
				string dataString = data[i];
				char dataCharForm[dataString.size()+1];
				strcpy(dataCharForm, dataString.c_str());
				char * token;

				token = strtok (dataCharForm,"/");
				splitData.push_back(token);
		        token = strtok (NULL,"/");


	            //Put properties in this string into a vector
	            while (token != NULL)
	            {
	                splitData.push_back(token);
	                token = strtok (NULL, "/");
	            }

	            int index;
				//add data to vertex, normal, uv
				if(splitData.size() >= 1){
					index = stoi(splitData[0]);
					vertices.push_back(vert[index - 1]);
				}
				if(splitData.size() == 2){
					index = stoi(splitData[1]);
					uvs.push_back(uv[index - 1]);
				}
				if(splitData.size() == 3){
					if(splitData[1] != ""){
						index = stoi(splitData[1]);
						uvs.push_back(uv[index - 1]);
					}

					index = stoi(splitData[2]);
					normals.push_back(norm[index - 1]);				
				}

			}

			material = m;
			normal = (vertices[1]->pos - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos);
			normal.normalize();
			area = ((vertices[1]->pos - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;

		}		

		float getIntersect(Vec3 &rayO, Vec3 &rayD){
			//Find Plane

			float dist = 0;
			float A = normal.x;
			float B = normal.y;
			float C = normal.z;

			float D = -(A*vertices[0]->x + B*vertices[0]->y + C*vertices[0]->z);
			float denom = (A*rayD.x + B*rayD.y + C*rayD.z);
			if(denom == 0){
				return -1;
			}

			float num = -(A*rayO.x + B*rayO.y + C*rayO.z + D);
			dist =  num/denom;

			Vec3 p = rayO + rayD * dist;

			//Find if inside triangle; 			
			float areaA = ((p - vertices[1]->pos)*(vertices[2]->pos - vertices[1]->pos)).magnitude()/2;
			float areaB = ((p - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;
			float areaC = ((p - vertices[0]->pos)*(vertices[1]->pos - vertices[0]->pos)).magnitude()/2;
			
			float alpha = areaA/area;
			float beta = areaB/area;
			float gamma = areaC/area;

			if(alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && areaA + areaB + areaC <= area + .0001){
 				return dist;
			}
			else{
				return -1;
			}

		}

		Vec3 getNormal(Vec3 &intersect){
			return normal;
		}


	private:
		
}; // end SomeClass

#endif
