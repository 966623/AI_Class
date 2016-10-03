#ifndef Object_HPP
#define Object_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"
#include "Material.hpp"
#include "Entity.hpp"

using namespace std;

class Object: public Entity {
	public:

		Vec3 pos;
		Material *material;

		Object (){

		}

		void translate(Vec3 &offset){
			pos = offset + pos;
		}

		virtual float getIntersect(Vec3 &rayO, Vec3 &rayD){
			cout << "NEED TO IMPLEMENT GETINTERSECT\n";
			return 0;
		}

		virtual Vec3 getNormal(Vec3 &intersect){
			cout << "NEED TO IMPLEMENT GETNORMAL\n";
			Vec3 i = Vec3(0,0,0);
			return i;
		}

	private:
		
}; // end SomeClass

#endif
