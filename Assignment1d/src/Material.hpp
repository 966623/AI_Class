#ifndef Material_HPP
#define Material_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include "Vec3.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Material{
	public:

		Vec3 color;
		Vec3 specColor;
		float ka;
		float kd;
		float ks;
		float n;
		float opacity;
		float refrac;

		Material (){

		}

		Material (vector<string> &data){
			if(data.size() != 12){
		        cout << "ERROR: INVALID MATERIAL\n";
		        exit(EXIT_FAILURE);
		    }

			color = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
			specColor = Vec3(stof(data[3]), stof(data[4]), stof(data[5]));
			ka = stof(data[6]);
			kd = stof(data[7]);
			ks = stof(data[8]);
			n = stof(data[9]);
			opacity = stof(data[10]);
			refrac = stof(data[11]);
		}		

	private:
		
}; // end SomeClass

#endif
