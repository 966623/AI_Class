#ifndef Ellipsoid_HPP
#define Ellipsoid_HPP

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

using namespace std;

class Ellipsoid: public Object {
	public:

		Vec3 radius;

		Ellipsoid (){

		}

		Ellipsoid (vector<string> &data, Material* m){
			if(data.size() != 6){
                cout << "ERROR: INVALID ELLIPSOID\n";
                exit(EXIT_FAILURE);
            }
            
			pos = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			radius = Vec3(stof(data[3]), stof(data[4]), stof(data[5]));
			material = m;
		}		

		float getIntersect(Vec3 &rayO, Vec3 &rayD){
			float A = pow(rayD.x/radius.x, 2) + pow(rayD.y/radius.y, 2) + pow(rayD.z/radius.z, 2);
			float B =  2.0*((rayD.x/radius.x) * ((rayO.x - pos.x)/radius.x) + 
							(rayD.y/radius.y) * ((rayO.y - pos.y)/radius.y) + 
							(rayD.z/radius.z) * ((rayO.z - pos.z)/radius.z));
			float C = pow((rayO.x - pos.x)/radius.x, 2.0) + pow((rayO.y - pos.y)/radius.y, 2.0) + pow((rayO.z - pos.z)/radius.z, 2.0) - 1;
			float det = pow(B, 2.0) - 4.0*A*C;
			if(det == 0){
				return -B/(2.0*A);
			}
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

		virtual Vec3 getNormal(Vec3 &intersect){
			Vec3 n = intersect-pos;
			n = Vec3(n.x/(radius.x*radius.x), n.y/(radius.y*radius.y), n.z/(radius.z*radius.z));
			return n.normalized();
		}

	private:
		
}; // end SomeClass

#endif
