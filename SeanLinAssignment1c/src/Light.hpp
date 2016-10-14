#ifndef Light_HPP
#define Light_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"
#include "Entity.hpp"

using namespace std;

class Light: public Entity {
	public:
		Vec3 color;
		bool isGlobal;

		virtual Vec3 getDir(Vec3 &p){
			return Vec3(0,0,0);
		}

	private:
		
}; // end SomeClass

#endif
