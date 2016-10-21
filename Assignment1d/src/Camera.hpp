#ifndef Camera_HPP
#define Camera_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Entity.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Camera: public Entity {
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
		bool perspective;

		Camera (){

		}

		Camera (float newRatio, vector<string> &eyeLoc, vector<string> &newupdir, vector<string> &newviewdir, vector<string> &newfov){
			//Check INput
			//Location
			if(eyeLoc.size() != 3){
		        cout << "ERROR: VALID X Y Z CAMERA COORDINATES REQUIRED\n";
		        exit(EXIT_FAILURE);
		    }
		    pos = Vec3(stof(eyeLoc[0]), stof(eyeLoc[1]), stof(eyeLoc[2]));

		    // Up direction
		    if(newupdir.size() != 3){
		        cout << "ERROR: VALID UP DIRECTION VECTOR REQUIRED\n";
		        exit(EXIT_FAILURE);
		    }
		    
		    updir = Vec3(stof(newupdir[0]), stof(newupdir[1]), stof(newupdir[2]));

		    if(updir.magnitude() == 0){
		        cout << "ERROR: UP DIRECTION VECTOR MUST HAVE NON ZERO LENGTH\n";
		        exit(EXIT_FAILURE);
		    }

		    // View direction
		    if(newviewdir.size() != 3){
		        cout << "ERROR: VALID VIEW DIRECTION VECTOR REQUIRED\n";
		        exit(EXIT_FAILURE);
		    }
		    
		    Vec3 viewdir = Vec3(stof(newviewdir[0]), stof(newviewdir[1]), stof(newviewdir[2]));

			if(viewdir.magnitude() == 0){
		        cout << "ERROR: VIEW DIRECTION VECTOR MUST HAVE NON ZERO LENGTH\n";
		        exit(EXIT_FAILURE);
		    }

		    // Vertical Field of View
		    if(newfov.size() < 1){
		        cout << "ERROR: VERTICAL FIELD OF VIEW REQUIRED\n";
		        exit(EXIT_FAILURE);
		    }
		    if (stof(newfov[0]) >= 180){
		        cout << "ERROR: FOV MUST BE LESS THAN 180 DEGREES\n";
		        exit(EXIT_FAILURE);
		    }
		    float fov = stof(newfov[0]);

		    if((viewdir * updir).magnitude() <= 0){
		        cout << "ERROR: UP DIRECTION AND VIEW DIRECTION CANNOT BE PARALLEL\n";
		        exit(EXIT_FAILURE);
		    }

			updir.normalize();
			viewdir.normalize();
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

			perspective = true;

		}

		Ray getPixelRay(float width, float height, float x, float y){
			Vec3 rayDir;
			Vec3 rayStart;

			Vec3 offsetV = (ll - ul)/(height - 1);
    		Vec3 offsetH = (ur - ul)/(width - 1);
    		Vec3 rayEnd = ul + (y*offsetV) + (x*offsetH);

			if(perspective){
				
	            rayDir = rayEnd - pos;
	            rayStart = pos;

			}
			else{
				rayDir = w;
				rayStart = rayEnd - w;
			}
			return Ray(rayStart, rayDir);
			
		}

		void setPerspective(bool b){
			perspective = b;
		}

		

	private:
		
}; // end SomeClass

#endif
