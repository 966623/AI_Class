#ifndef Scene_HPP
#define Scene_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Vec3.hpp"
#include "Material.hpp"
#include "ImgSettings.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include "Object.hpp"
#include "Sphere.hpp"
#include "Texture.hpp"
#include "Ellipsoid.hpp"
#include "Phong.hpp"
#include "Light.hpp"
#include "Basiclight.hpp"
#include "Spotlight.hpp"
#include "Polygon.hpp"
#include "Triangle.hpp"
#include "Vertex.hpp"
#include "UvCoord.hpp"
#include "Normal.hpp"
#include "SceneTree.hpp"

using namespace std;

class Scene{
	public:
		Image img;
	    Camera cam;
	    vector<Object*> objects;
	    vector<Material*> materials;
	    vector<Light*> lights;
	    vector<Vertex*> vertices;
	    vector<Polygon*> polygons;
	    vector<Normal*> normals;
	    vector<UvCoord*> uvs;
	    vector<Texture*> textures;
	    SceneTree sceneTree;

	    void render(ofstream &file){

		    cout << "\nRendering...\n";
		    if(objects.size() == 0){
		        cout << "ERROR: No objects to render\n";
		        exit(EXIT_FAILURE);
		    }
		    cout << "Creating bounding box tree\n";
		    makeSceneTree();
		    Phong phongRender = Phong();
		    cout << "Rendering pixels\n";
		    // Calculate pixels
		    for(int y = 0; y < img.height; y++){
		        for(int x = 0; x < img.width; x++){
		            cout << "\rPixel: " << x << " " << y;
		            //Define ray

		            Ray renderRay = cam.getPixelRay(img.width, img.height, x, y);

		            float distance = -1;
		            Object* closestObject = objects[0];
		            
		            distance = sceneTree.getIntersect(renderRay);
		         	closestObject = renderRay.hit;
		            // Choose nearest intersection and write color to image. If no intersection write background color
		            if (distance < 0){
		                img.set(x, y, img.bkg);
		            }
		            else{
		                Vec3 intersect = renderRay.pos + (distance*renderRay.dir);
		                
		                img.set(x, y, phongRender.calc(intersect, &cam, closestObject, lights, sceneTree));
		            }
		        }
		    }

		    img.write(file);
		    file.close();
    		cout << "\nImage successfully created\n";
		}

		void makeSceneTree(){
			sceneTree = SceneTree(objects);
		}

	private:
		
}; // end SomeClass

#endif
