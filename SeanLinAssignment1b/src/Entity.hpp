#ifndef Entity_HPP
#define Entity_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"

using namespace std;

class Entity {
	public:

		Vec3 pos;

		Entity (){

		}

		void translate(Vec3 offset){
			pos = offset + pos;
		}

	private:
		
}; // end SomeClass

#endif
