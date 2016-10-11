#ifndef Spotlight_HPP
#define Spotlight_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Vec3.hpp"
#include "Light.hpp"

using namespace std;

class Spotlight: public Light {
	public:

		float theta;
		Vec3 dir;
		Spotlight(){

		}

		Spotlight(vector<string> &data){
			if(data.size() != 10){
                cout << "ERROR: SPOTLIGHT IS INVALID\n";
                exit(EXIT_FAILURE);
            }

			pos = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			dir = Vec3(stof(data[3]), stof(data[4]), stof(data[5]));
			dir.normalize();
			if(dir.magnitude() == 0){
				cout << "ERROR: SPOTLIGHT DIRECTION CANNOT BE ZERO VECTOR\n";
                exit(EXIT_FAILURE);
			}
			theta = stof(data[6]);
			color = Vec3(stof(data[7]), stof(data[8]), stof(data[9]));
			isGlobal = false;
		}

		Vec3 getDir(Vec3 &p){
			Vec3 toP = (p-pos).normalized();
			float angle = acos(toP.dot(dir));
			angle = angle/(4*atan(1)) * 180;
			if(angle <= theta){
				return toP * -1;
			}
			else{
				return Vec3(0,0,0);
			}
		}

	private:
		
}; // end SomeClass

#endif
