#ifndef Basiclight_HPP
#define Basiclight_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"
#include "Light.hpp"

using namespace std;

class Basiclight:public Light {
	public:
		
		float w;
		Basiclight(){

		}

		Basiclight(vector<string> &data){
			if(data.size() != 7){
                cout << "ERROR: POINT/DIRCTIONAL LIGHT IS INVALID\n";
                exit(EXIT_FAILURE);
            }

			pos = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			w = stof(data[3]);
			color = Vec3(stof(data[4]), stof(data[5]), stof(data[6]));
			if (w == 1){
				isGlobal = false;
			}
			else{
				isGlobal = true;
			}
		}

		Vec3 getDir(Vec3 &p){
			if (isGlobal){
				return pos.normalized() * -1;
			}
			else{
				return (pos - p).normalized();
			}
		}

	private:
		
}; // end SomeClass

#endif
