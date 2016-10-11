#ifndef Normal_HPP
#define Normal_HPP

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

class Normal{
	public:

		Vec3 dir;
		float x;
		float y;
		float z;
		Normal (){

		}

		Normal (vector<string> &data){
			x = stof(data[0]);
			y = stof(data[1]);
			z = stof(data[2]);
			dir = Vec3(x, y, z);
		}		

	private:
		
}; // end SomeClass

#endif

