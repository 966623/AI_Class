#ifndef Object_HPP
#define Object_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"

using namespace std;

class Object {
	public:

		Vec3 pos;
		int material;

		Object (){

		}

		void translate(Vec3 offset){
			pos = offset + pos;
		}

		virtual float getIntersect(Vec3 rayO, Vec3 rayD){
			cout << "NEED TO IMPLEMENT\n";
			return 0;
		}
		

		

	private:
		
}; // end SomeClass

#endif
