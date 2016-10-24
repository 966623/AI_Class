#ifndef Ray_HPP
#define Ray_HPP
#define _USE_MATH_DEFINES

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include "Vec3.hpp"

using namespace std;
class Object;

class Ray {
	public:

		Vec3 pos;
		Vec3 dir;
		Vec3 color;
		float distance;
		Object* hit;
		Ray (){

		}

		Ray (Vec3 p, Vec3 d){
			pos = p;
			dir = d;
			distance = dir.magnitude();
			dir.normalize();
		}

		//
		friend Ray operator+(const Ray &r, const Vec3 &v){
			float xTotal = r.dir.x + v.x;
			float yTotal = r.dir.y + v.y;
			float zTotal = r.dir.z + v.z;
			Vec3 newDir = Vec3(xTotal, yTotal, zTotal);
			return Ray(r.pos, newDir);
		}

		friend Ray operator-(const Ray &r, const Vec3 &v){
			float xTotal = r.dir.x - v.x;
			float yTotal = r.dir.y - v.y;
			float zTotal = r.dir.z - v.z;
			Vec3 newDir = Vec3(xTotal, yTotal, zTotal);
			return Ray(r.pos, newDir);
		}

		friend Ray operator*(const Ray &r, const float &f){
			return Ray(r.pos, r.dir*f*r.distance);
		}

		friend Ray operator/(const Ray &r, const float &f){
			return Ray(r.pos, r.dir*r.distance/f);
		}


	private:
		
}; // end SomeClass

#endif
