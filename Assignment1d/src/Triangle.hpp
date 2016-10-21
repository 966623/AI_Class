#ifndef Triangle_HPP
#define Triangle_HPP

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
#include "Polygon.hpp"
#include "Vertex.hpp"

using namespace std;

class Triangle: public Polygon {
	public:

		Triangle (){

		}

		Triangle (vector<string> &data, Material *m){
			
		}		

		float getIntersect(Vec3 &rayO, Vec3 &rayD){

			return 0;
		}


	private:
		
}; // end SomeClass

#endif
