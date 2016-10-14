#ifndef UvCoord_HPP
#define UvCoord_HPP

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

class UvCoord{
	public:

		Vec3 coord;
		float x;
		float y;
		float z;
		UvCoord (){

		}

		UvCoord (vector<string> &data){
			if(data.size() != 2){
				cout << "ERROR: Invalid UV Coordinate";
				exit(EXIT_FAILURE);
			}
			x = stof(data[0]);
			y = 1-stof(data[1]);
			if (x < 0){
				x = -x;
			}

			if (y < 0){
				y = -y;
			}
			if(x > 1){
				x = 1;
			}
			if(y > 1){
				y = 1;
			}
			z = 0;
			coord = Vec3(x, y, z);
		}		

	private:
		
}; // end SomeClass

#endif
