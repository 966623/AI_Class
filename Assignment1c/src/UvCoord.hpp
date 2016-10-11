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
			x = stof(data[0]);
			y = stof(data[1]);
			z = 0;
			coord = Vec3(x, y, z);
		}		

	private:
		
}; // end SomeClass

#endif
