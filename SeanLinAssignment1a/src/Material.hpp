#ifndef Material_HPP
#define Material_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include "Vec3.hpp"

using namespace std;

class Material{
	public:

		Vec3 color;

		Material (){

		}

		Material (vector<string> data){
			color = Vec3(stof(data[0]), stof(data[1]), stof(data[2]));
		}		

	private:
		
}; // end SomeClass

#endif
