#ifndef Sphere_HPP
#define Sphere_HPP
#define _USE_MATH_DEFINES

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vec3.hpp"
#include "Object.hpp"
#include "Material.hpp"
#include "Ray.hpp"


using namespace std;

class Sphere: public Object {
	public:

		float radius;

		Sphere (){

		}

		Sphere (vector<string> &data, Material *m){
			if(data.size() != 4){
                cout << "ERROR: INVALID SPHERE\n";
                exit(EXIT_FAILURE);
            }

			pos = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			radius = stof(data[3]);
			size = Vec3(radius*2, radius*2, radius*2);
			material = m;
		}		

		float getIntersect(Ray &ray){
			Vec3 rayO = ray.pos;
			Vec3 rayD = ray.dir;
			//magic equation that finds intersections
			float A = 1.0;
			float B =  2.0*(rayD.x * (rayO.x - pos.x) + rayD.y * (rayO.y - pos.y) + rayD.z * (rayO.z - pos.z));
			float C = pow(rayO.x - pos.x, 2.0) + pow(rayO.y - pos.y, 2.0) + pow(rayO.z - pos.z, 2.0) - pow(radius, 2.0);
			float det = pow(B, 2.0) - 4.0*A*C;
			if(det == 0){
				return -B/(2.0*A);
			}

			//get closest intersection
			else if(det > 0){
				float sol1 = (-B + sqrt(det))/(2.0*A);
				float sol2 = (-B - sqrt(det))/(2.0*A);
				if (sol1 < sol2){
					return sol1;
				}
				else {
					return sol2;
				}
			}
			else{
				return -1;
			}
		}

		Vec3 getColor(Vec3 &p){
			if(textured){

				float nx = (p.x - pos.x)/radius;
				float ny = (p.y - pos.y)/radius;
				float nz = (p.z - pos.z)/radius;
				float y = acos(ny);
				y = y/M_PI;
				float x = atan2(nz, nx);
				x = x/(2*M_PI) + .5;
				x = 1-x;
				Vec3 uvCoord = Vec3(x, y, 0);
				return texture->getColor(uvCoord);
			}
			else{
				return material->color;
			}
			
		}

		Vec3 getNormal(Vec3 &intersect){
			return (intersect - pos).normalized();
		}

	private:
		
}; // end SomeClass

#endif
