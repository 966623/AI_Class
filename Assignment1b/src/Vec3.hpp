#ifndef Vec3_HPP
#define Vec3_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>

using namespace std;

class Vec3 {
	public:

		Vec3 (){

		}

		Vec3 (float newX, float newY, float newZ){
			x = newX;
			y = newY;
			z = newZ;
		}

		float x;
		float y;
		float z;

		//
		friend Vec3 operator+(const Vec3 &v1, const Vec3 &v2){
			float xTotal = v1.x + v2.x;
			float yTotal = v1.y + v2.y;
			float zTotal = v1.z + v2.z;
			return Vec3(xTotal, yTotal, zTotal);
		}

		friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2){
			float xTotal = v1.x - v2.x;
			float yTotal = v1.y - v2.y;
			float zTotal = v1.z - v2.z;
			return Vec3(xTotal, yTotal, zTotal);
		}

		friend Vec3 operator*(const Vec3 &v1, const Vec3 &v2){
			float xTotal = v1.y*v2.z - v1.z*v2.y;
			float yTotal = v1.z*v2.x - v1.x*v2.z;
			float zTotal = v1.x*v2.y - v1.y*v2.x;
			return Vec3(xTotal, yTotal, zTotal);
		}

		friend Vec3 operator*(const float &f, const Vec3 &v2){
			return Vec3(v2.x * f, v2.y * f, v2.z * f);
		}

		friend Vec3 operator*(const Vec3 &v1, const float &f){
			return Vec3(v1.x * f, v1.y * f, v1.z * f);
		}

		friend Vec3 operator/(const Vec3 &v1, const float &f){
			return Vec3(v1.x / f, v1.y / f, v1.z / f);
		}

		float dot(Vec3 &v){
			return x*v.x + y*v.y + z*v.z;
		}
		
		void normalize(){
			float len = magnitude();
			x = x/len;
			y = y/len;
			z = z/len;
		}

		Vec3 normalized(){

			float len = magnitude();
			return Vec3(x/len, y/len, z/len);
		}

		float magnitude(){
			return sqrt(x*x + y*y + z*z);
		}

		bool equals(Vec3 &v){
			return (x == v.x) && (y == v.y) && (z == v.z);
		}

		void clamp(float min, float max){
			if (x < min)
				x = min;
			if (y < min)
				y = min;
			if (z < min)
				z = min;
			if (x > max)
				x = max;
			if (y > max)
				y = max;
			if (z > max)
				z = max;


		}

		string to_str(){
			stringstream ss;
			ss << "<" << x << ", " << y << ", " << z << ">\n";
			return ss.str();
		}

	private:
		
}; // end SomeClass

#endif
