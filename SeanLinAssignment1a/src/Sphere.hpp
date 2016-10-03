#ifndef Sphere_HPP
#define Sphere_HPP

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

using namespace std;

class Sphere: public Object {
	public:

		float radius;

		Sphere (){

		}

		Sphere (vector<string> data, int m){
			pos = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			radius = stof(data[3]);
			material = m;
		}		

		float getIntersect(Vec3 rayO, Vec3 rayD){

			//magic equation that finds intersections
			float A = 1.0;
			float B =  2.0*(rayD.x * (rayO.x - pos.x) + rayD.y * (rayO.y - pos.y) + rayD.z * (rayO.z - pos.z));
			float C = pow(rayO.x - pos.x, 2.0) + pow(rayO.y - pos.y, 2.0) + pow(rayO.z - pos.z, 2.0) - pow(radius, 2.0);
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

	private:
		
}; // end SomeClass

#endif
