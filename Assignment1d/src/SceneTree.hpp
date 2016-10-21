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
		SceneTree* leftChild;
		SceneTree* rightChild;
		Object* data;

		SceneTree (){

		}

		SceneTree(Object* o){
			data = o;
			upperCorner = Vec3(data->pos[0] + data->size[0]/2, data->pos[1] + data->size[1]/2, data->pos[2] + data->size[2]/2);
			lowerCorner = Vec3(data->pos[0] - data->size[0]/2, data->pos[1] - data->size[1]/2, data->pos[2] - data->size[2]/2);
			center = o->pos;
		}

		SceneTree (vector<Object*> obj){
			cout << "SIZE: " << obj.size() << "\n";
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
				//pair up all nodes
				cout << "SIZE_1: " << obj.size() << "\n";
				tempSceneTree.resize(0);
				while(finalSceneTree.size() > 0){
					cout << "SIZE_2: " << obj.size() << "\n";
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
							cout << "COUNT: " << i << "\n";
							cout << "THING: " << finalSceneTree[i] << "\n";
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

			cout << "HERE\n";
			if(finalSceneTree[0]->leftChild != NULL){
				leftChild = finalSceneTree[0]->leftChild;
			}
			if(finalSceneTree[0]->rightChild != NULL){
				rightChild = finalSceneTree[0]->rightChild;
			}
			if(finalSceneTree[0]->data != NULL){
				data = finalSceneTree[0]->data;
			}	
		}	

		float getIntersect(Ray &ray){
			
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
			if(leftChild != NULL){
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
