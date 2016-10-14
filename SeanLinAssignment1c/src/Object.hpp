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
#include "Texture.hpp"
#include "Entity.hpp"

using namespace std;

class Object: public Entity {
	public:

		Vec3 pos;
		bool textured;
		Material *material;
		Texture *texture;

		virtual void setTexture(Texture* t){
			textured = true;
			texture = t;
		}

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

		virtual Vec3 getColor(Vec3 &p){
			Vec3 i = Vec3(0,0,0);
			return i; 
		}

	private:
		
}; // end SomeClass

#endif
