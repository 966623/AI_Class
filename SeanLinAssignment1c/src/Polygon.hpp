#ifndef Polygon_HPP
#define Polygon_HPP

#include "Object.hpp"
#include "Material.hpp"
#include "Vertex.hpp"
#include "Normal.hpp"
#include "UvCoord.hpp"
#include "Texture.hpp"
#include <algorithm>
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

		void setTexture(Texture* t){
			textured = true;
			texture = t;
			if (uvs.size() == 0){
				textured = false;
			}
		}
		
		

		Polygon (vector<string> &data, vector<Vertex*> &vert, vector<Normal*> &norm, vector<UvCoord*> &uv, Material* m){
			if(data.size() != 3){
				cout << "ERROR: Invalid Polygon, must have 3 vertices.\n";
				exit(EXIT_FAILURE);
			}

			for(int i = 0; i < 3; i++){
				vector<string> splitData;
				string dataString = data[i];

				size_t t = dataString.find("//");
				if(t != string::npos){
					dataString.replace(t, 2, "/ /");
				}
				
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
					if(index > vert.size()){
						cout << "ERROR: Vertex not found for polygon\n";
						exit(EXIT_FAILURE);
					}
					vertices.push_back(vert[index - 1]);
				}
				if(splitData.size() == 2){
					index = stoi(splitData[1]);
					if(index > uv.size()){
						cout << "ERROR: texture coordinate not found for polygon\n";
						exit(EXIT_FAILURE);
					}
					uvs.push_back(uv[index - 1]);
				}
				if(splitData.size() == 3){
					if(splitData[1] != " "){
						index = stoi(splitData[1]);
						if(index > uv.size()){
							cout << "ERROR: texture coordinate not found for polygon\n";
							exit(EXIT_FAILURE);
						}
						uvs.push_back(uv[index - 1]);
					}
					index = stoi(splitData[2]);
					if(index > norm.size()){
						cout << "ERROR: normal not found for polygon\n";
						exit(EXIT_FAILURE);
					}
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

			if(alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1 && areaA + areaB + areaC <= area + .00001){
 				return dist;
			}
			else{
				return -1;
			}

		}

		Vec3 getNormal(Vec3 &intersect){
			if(normals.size() == 0){
				return normal;
			}
			float area = ((vertices[1]->pos - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;
			float areaA = ((intersect - vertices[1]->pos)*(vertices[2]->pos - vertices[1]->pos)).magnitude()/2;
			float areaB = ((intersect - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;
			float areaC = ((intersect - vertices[0]->pos)*(vertices[1]->pos - vertices[0]->pos)).magnitude()/2;
			
			float alpha = areaA/area;
			float beta = areaB/area;
			float gamma = areaC/area;
			Vec3 v = (alpha*normals[0]->dir + beta*normals[1]->dir + gamma*normals[2]->dir);
			Vec3 n = v/v.magnitude();
			n.normalize();
			return n;
		}

		Vec3 getColor(Vec3 &p){

			if(textured){
				float area = ((vertices[1]->pos - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;
				float areaA = ((p - vertices[1]->pos)*(vertices[2]->pos - vertices[1]->pos)).magnitude()/2;
				float areaB = ((p - vertices[0]->pos)*(vertices[2]->pos - vertices[0]->pos)).magnitude()/2;
				float areaC = ((p - vertices[0]->pos)*(vertices[1]->pos - vertices[0]->pos)).magnitude()/2;
				
				float alpha = areaA/area;
				float beta = areaB/area;
				float gamma = areaC/area;
				Vec3 newCoord = Vec3(alpha*uvs[0]->x + beta*uvs[1]->x + gamma*uvs[2]->x, alpha*uvs[0]->y + beta*uvs[1]->y + gamma*uvs[2]->y, 0);
				return texture->getColor(newCoord);
			}
			else{
				return material->color;
			}
		}

		void to_str(){
			string s = "";
			s += "Vertices: ";
			for(int i = 0; i < 3; i++){

			}
		}


	private:
		
}; // end SomeClass

#endif
