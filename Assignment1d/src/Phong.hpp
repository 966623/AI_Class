#ifndef Phong_HPP
#define Phong_HPP
#define _USE_MATH_DEFINES
#include <tuple>
#include <vector>
#include <sstream>
#include <string.h>
#include <math.h>
#include <algorithm>
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
		int reflect_depth = 5;

		Phong(){

		}

		Vec3 calc(Vec3 &intersect, Ray &r, Object *o, vector<Light*> &l, SceneTree &tree){
			return calc(intersect, r, o, l, tree, 0);
		}

		Vec3 calc(Vec3 &intersect, Ray &r, Object *o, vector<Light*> &l, SceneTree &tree, int depth){
			Material* mat = o->material;
			Texture* tex = o->texture;
			Vec3 color;
			color = o->getColor(intersect);
			Vec3 N = o->getNormal(intersect);  //Normal

			Vec3 V = r.dir.normalized() * -1; //View direction

			color = (mat->ka * color); //Ambient

			//Check each light for shadow
			for(int i = 0; i < l.size(); i++){
				int S = 1;
				Light* currentLight = l[i];
				Vec3 L = currentLight->getDir(intersect); // Light direciton
	            float distance = -1;


	            //Shadow
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

	            //diffuse and spec
				Vec3 H = (L + V).normalized();
				Vec3 currentColor = (mat->kd * color * N.dot(L)) + (mat->ks * mat->specColor * pow(N.dot(H), mat->n));
				currentColor.clamp(0,1);
				color = color + S * Vec3(currentLight->color.x * currentColor.x, currentLight->color.y * currentColor.y, currentLight->color.z * currentColor.z);


				if(mat->opacity != 1){
					//transparency
					Vec3 I = V;
					Vec3 ref = sqrt(1 - ( pow(1 / mat->refrac, 2) * (1 - pow(N.dot(I), 2)))) * (-1 * N) + (1 / mat->refrac) * ( (N.dot(I) * N) - I);
					Ray refRay = Ray(intersect, ref);
					color = color + refract(intersect, refRay, I, o, l, tree, depth);
				}
				//Reflectance
				else if(mat->refrac != 1){
					//reflection
					Vec3 I = V;
					float alpha = N.dot(I);
					Vec3 ref = 2 * (alpha * N) - I;
					Ray refRay = Ray(intersect, ref);
					color = color + reflect(intersect, refRay, o, l, tree, depth);
				}

				

				
			}
			color.clamp(0,1);
			return color;
		}

		Vec3 reflect(Vec3 &intersect, Ray& r, Object *o, vector<Light*> &l, SceneTree &tree, int depth){
			Material* mat = o->material;
			Texture* tex = o->texture;
			Vec3 i = r.dir.normalized();
			Vec3 n = o->getNormal(intersect).normalized();
			float f0 = pow((mat->refrac - 1)/(mat->refrac + 1), 2);
			float ci = i.dot(n);
			float fr = f0 + (1 - f0) * pow(1 - ci, 5);


			float distance = tree.getIntersect(r);
		    Object* closestObject = r.hit;
		    Vec3 p = r.pos + r.dir * distance;

		    if(distance < .00001 || depth > reflect_depth){
		    	return Vec3(0,0,0);
		    }else{
		    	Vec3 color = calc(p, r, closestObject, l, tree, depth + 1);
				return color * fr;
		    }
			
		}
		
		Vec3 refract(Vec3 &intersect, Ray& r, Vec3& iVec, Object *o, vector<Light*> &l, SceneTree &tree, int depth){
			Material* mat = o->material;
			Texture* tex = o->texture;
			Vec3 i = r.dir.normalized();
			Vec3 n = o->getNormal(intersect).normalized();
			float f0 = pow((mat->refrac - 1)/(mat->refrac + 1), 2);
			float ci = iVec.dot(n);
			float fr = f0 + (1 - f0) * pow(1 - ci, 5);


			float distance = tree.getIntersect(r);
		    Object* closestObject = r.hit;
		    Vec3 p = r.pos + r.dir * distance;

		    if(distance < .00001 || depth > reflect_depth){
		    	return Vec3(0,0,0);
		    }else{
		    	Vec3 color = calc(p, r, closestObject, l, tree, depth + 1);
				return color * (1 - fr) * (1 - mat->opacity);
		    }
			
		}

		

	private:
		
}; // end SomeClass

#endif
