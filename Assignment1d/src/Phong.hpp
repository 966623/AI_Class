#ifndef Phong_HPP
#define Phong_HPP
#define _USE_MATH_DEFINES
#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <iostream>
#include "Vec3.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Polygon.hpp"
#include "Ray.hpp"
#include "SceneTree.hpp"


using namespace std;

class Phong {
	public:
		Phong(){

		}

		Vec3 calc(Vec3 &intersect, Camera *c, Object *o, vector<Light*> &l, SceneTree &tree){
			Material* mat = o->material;
			Texture* tex = o->texture;
			Vec3 color;
			color = o->getColor(intersect);
			Vec3 N = o->getNormal(intersect);  //Normal

			Vec3 V = (c->pos - intersect).normalized(); //View direction

			color = (mat->ka * color); //Ambient

			//Check each light for shadow
			for(int i = 0; i < l.size(); i++){
				int S = 1;
				Light* currentLight = l[i];
				Vec3 L = currentLight->getDir(intersect); // Light direciton
	            float distance = -1;

	            Ray lightRay = Ray(intersect, L);
				//If light touches point
				if(L.magnitude() > 0){
		            distance = tree.getIntersect(lightRay);
				}

	            if(distance <= 0.00001){
	            	//No shadow
	            	S = 1;
	            }
	            else{
	            	//If global light (non point)
	            	if(currentLight->isGlobal){
	            		S = 0;
	            	}
	            	else{
	            		if(distance <= (currentLight->pos-intersect).magnitude()){
	            			S = 0;
	            		}
	            		else{
	            			S=1;
	            		}
	            	}
	            }

				Vec3 H = (L + V).normalized();
				Vec3 currentColor = (mat->kd * color * N.dot(L)) + (mat->ks * mat->specColor * pow(N.dot(H), mat->n));
				currentColor.clamp(0,1);
				color = color + S * Vec3(currentLight->color.x * currentColor.x, currentLight->color.y * currentColor.y, currentLight->color.z * currentColor.z);
				
			}
			color.clamp(0,1);
			return color;
		}
		

		

	private:
		
}; // end SomeClass

#endif
