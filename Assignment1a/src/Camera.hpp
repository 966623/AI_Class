#ifndef Camera_HPP
#define Camera_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include "Vec3.hpp"
#include "Object.hpp"

using namespace std;

class Camera: public Object {
	public:

		Vec3 updir;
		Vec3 viewdir;
		float fov;
		float ratio;
		Vec3 ul;
		Vec3 ur;
		Vec3 ll;
		Vec3 lr;
		Vec3 u;
		Vec3 v;
		Vec3 w;
		float height;
		float width;

		Camera (){

		}

		Camera (Vec3 newPos, Vec3 newUpdir, Vec3 newViewdir, float newFov, float newRatio){
			pos = newPos;
			newUpdir.normalize();
			newViewdir.normalize();
			updir = newUpdir;
			viewdir = newViewdir;
			fov = newFov;
			float d = 1.0;

			ratio = newRatio;

			//find u, v, w
			u = viewdir*updir;
			u.normalize();
			v = u*viewdir;
			v.normalize();
			w = viewdir;
			w.normalize();

			//find height, width
			height = 2*d*tan((fov/180 * (4*atan(1))) / 2);
			width = ratio * height;

			//find window corners
			ul = (pos + d*w) - u*(width/2) + v*(height/2);
			ur = (pos + d*w) + u*(width/2) + v*(height/2);
			ll = (pos + d*w) - u*(width/2) - v*(height/2);
			lr = (pos + d*w) + u*(width/2) - v*(height/2);

		}


		

	private:
		
}; // end SomeClass

#endif
