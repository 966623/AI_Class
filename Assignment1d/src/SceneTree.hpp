#ifndef SceneTree_HPP
#define SceneTree_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits>
#include "Vec3.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Ray.hpp"

using namespace std;

class SceneTree{
	public:
		Vec3 center;
		Vec3 upperCorner;
		Vec3 lowerCorner;
		SceneTree* leftChild = NULL;
		SceneTree* rightChild = NULL;
		Object* data = NULL;

		SceneTree (){

		}

		SceneTree(Object* o){
			data = o;
			upperCorner = Vec3(data->pos[0] + data->size[0]/2, data->pos[1] + data->size[1]/2, data->pos[2] + data->size[2]/2);
			lowerCorner = Vec3(data->pos[0] - data->size[0]/2, data->pos[1] - data->size[1]/2, data->pos[2] - data->size[2]/2);
			center = data->pos;
			
		}

		SceneTree (vector<Object*> obj){
			cout << "Number of Objects: " << obj.size() << "\n";
			//Create leaves
			vector<SceneTree*> leaves;
			leaves.resize(obj.size());
			for(int i = 0; i < leaves.size(); i++){
				leaves[i] = new SceneTree(obj[i]);
			}
			if(leaves.size() == 1){
				leftChild = leaves[0];
				upperCorner = leftChild->upperCorner;
				lowerCorner = leftChild->lowerCorner;
				return;
			}

			vector<SceneTree*> finalSceneTree = leaves;
			vector<SceneTree*> tempSceneTree;
			//pair all nodes until one root remaining
			while(finalSceneTree.size() != 1){
				cout << "Trees: " << finalSceneTree.size() << "\n";
				//pair up all nodes
				tempSceneTree.resize(0);
				while(finalSceneTree.size() > 0){

					//get first node
					SceneTree* first = finalSceneTree[0];
					finalSceneTree = erase(finalSceneTree, 0);
					//Setup new node
					SceneTree* newTree = new SceneTree();
					newTree->leftChild = first;
					//If something exists to pair with

					if(finalSceneTree.size() > 0){
						//find leaf closest to it
						float minDist = (first->center - finalSceneTree[0]->center).magnitude();
						int closest = 0;
						for(int i = 0; i < finalSceneTree.size(); i++){
							float dist = (first->center - finalSceneTree[i]->center).magnitude();
							if(dist < minDist){
								minDist = dist;
								closest = i;
							}
						}
						//set closest to right child and remove from node list
						newTree->rightChild = finalSceneTree[closest];
						finalSceneTree = erase(finalSceneTree, closest);
						
					}
					
					newTree->setBounds();
					tempSceneTree.push_back(newTree);
					
				}
				finalSceneTree = tempSceneTree;
				
			}

			if(finalSceneTree[0]->leftChild != NULL){
				leftChild = finalSceneTree[0]->leftChild;
			}
			if(finalSceneTree[0]->rightChild != NULL){
				rightChild = finalSceneTree[0]->rightChild;
			}
			if(finalSceneTree[0]->data != NULL){
				data = finalSceneTree[0]->data;
			}

			setBounds();	
		}	

		float getIntersect(Ray &ray){
			tuple<float, Object*> t = getIntersectRecurse(ray);
			ray.hit =  get<1> (t);
			return get<0> (t);
		}

		tuple<float, Object*> getIntersectRecurse(Ray &ray){
			float minDist = -1;
			float maxDist = numeric_limits<float>::infinity();

			//check if ray intersects box
			Vec3 near;
			Vec3 far;
			for(int i = 0; i < 3; i++){
				if(upperCorner[i] - ray.pos[i] >= lowerCorner[i] - ray.pos[i]){
					near[i] = lowerCorner[i];
					far[i] = upperCorner[i];
				}
				else{
					near[i] = upperCorner[i];
					far[i] = lowerCorner[i];
				}
			}

			float x1 = (near.x - ray.pos.x)/ray.dir.x;
			float x2 = (far.x - ray.pos.x)/ray.dir.x;
			
			minDist = max(minDist, min(x1, x2));
			maxDist = min(maxDist, max(x1, x2));

    		float y1 = (near.y - ray.pos.y)/ray.dir.y;
			float y2 = (far.y - ray.pos.y)/ray.dir.y;
			minDist = max(minDist, min(y1, y2));
			maxDist = min(maxDist, max(y1, y2));

			float z1 = (near.z - ray.pos.z)/ray.dir.z;
			float z2 = (far.z - ray.pos.z)/ray.dir.z;
			minDist = max(minDist, min(z1, z2));
			maxDist = min(maxDist, max(z1, z2));
			
			//If intersect box, check if ray intersects contents
			if(maxDist >= minDist){
				float newdist = -1;
				Object* obj;
				ray.distance = -1;

				tuple<float, Object*>  l = make_tuple(-1, (Object*)0);
				tuple<float, Object*>  r = make_tuple(-1, (Object*)0);
				
				if(data != NULL){
					newdist = data->getIntersect(ray);
					obj = data;	
				}
				else{					
					if(leftChild != NULL){
						l = leftChild->getIntersectRecurse(ray);
					}
					if(rightChild != NULL){
						r = rightChild->getIntersectRecurse(ray);
					}


					if(get<0>(l) == -1 && get<0>(r) != -1){
						newdist = get<0>(r);
						obj = get<1>(r);
					}
					else if(get<0>(l) != -1 && get<0>(r) == -1){
						newdist = get<0>(l);
						obj = get<1>(l);
					}

					else if(get<0>(l) != -1 && get<0>(r) != -1){
						if(get<0>(l) < get<0>(r)){
							newdist = get<0>(l);
							obj = get<1>(l);
						}
						else{
							newdist = get<0>(r);
							obj = get<1>(r);
						}
						
					}
					
				}
				tuple<float, Object*> newTuple = make_tuple(newdist, obj);
				return newTuple;
			}
			else{
				tuple<float, Object*> newTuple = make_tuple(-1,(Object*)0);
				return newTuple;
			}

		}

		vector<SceneTree*> erase(vector<SceneTree*>  &v, int i){
			vector<SceneTree*> newV;
			newV.resize(v.size() - 1);
			int counter = 0;
			for(int x = 0; x < v.size(); x++){
				if(x != i){
					newV[counter] = v[x];
					counter++;
				}
			}
			return newV;
		}

		void setBounds(){
			if(data != NULL){
				upperCorner = Vec3(data->pos[0] + data->size[0]/2, data->pos[1] + data->size[1]/2, data->pos[2] + data->size[2]/2);
				lowerCorner = Vec3(data->pos[0] - data->size[0]/2, data->pos[1] - data->size[1]/2, data->pos[2] - data->size[2]/2);
				center = data->pos;
			}
			else if(leftChild != NULL){
				if(rightChild != NULL){

					upperCorner = leftChild->upperCorner;
					lowerCorner = leftChild->lowerCorner;
					for(int i = 0; i < 3; i++){
						if(upperCorner[i] < rightChild->upperCorner[i]){
							upperCorner[i] = rightChild->upperCorner[i];
						}
						if(lowerCorner[i] > rightChild->lowerCorner[i]){
							lowerCorner[i] = rightChild->lowerCorner[i];
						}
						center[i] = (lowerCorner[i] + upperCorner[i])/2;
					}
					

				}
				else{
					center = leftChild->center;
					upperCorner = leftChild->upperCorner;
					lowerCorner = leftChild->lowerCorner;
				}
			}

		}	

	private:
		

		
}; // end SomeClass

#endif
