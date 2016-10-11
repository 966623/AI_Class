#ifndef Vertex_HPP
#define Vertex_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vec3.hpp"
#include "Material.hpp"

using namespace std;

class Vertex{
	public:

		Vec3 pos;
		Vec3 normal;
		float x;
		float y;
		float z;
		Vertex (){

		}

		Vertex (vector<string> &data){
			x = stof(data[0]);
			y = stof(data[1]);
			z = stof(data[2]);
			pos = Vec3(x, y, z);
		}		

	private:
		
}; // end SomeClass

#endif
