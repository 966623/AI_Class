#ifndef Image_HPP
#define Image_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <fstream>
#include "Vec3.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Image {
	public:

		int height;
		int width;
		int maxColor = 255;
		vector<vector<Vec3>> pixels;
		Vec3 bkg;
		Image (){

		}

		Image (int w, int h, vector<string> &b){
			//error checking
			if(b.size() != 3){
		        bkg = Vec3(1, 1, 1);
		        cout << "Background color not specified, background color defaulted to white.\n";
		    }
		    else{
		        bkg = Vec3(stof(b[0]), stof(b[1]), stof(b[2]));
		    }    


			height = h;
			width = w;
			pixels.resize(h);
			for(int i = 0; i < h; i++){
				pixels[i].resize(w);
			}
		}

		void set(int x, int y, Vec3 c){
			if(x < 0 || x >= width || y < 0 || y >= height){
				return;
			}
			pixels[y][x] = c;
		}

		void write(ofstream &file){
			for(int y = 0; y < height; y++){
        		for(int x = 0; x < width; x++){
        			Vec3 c = pixels[y][x];
        			file << (int)(c.x * maxColor) << " " << (int)(c.y * maxColor) << " "  << (int)(c.z * maxColor )<< "\n";
        		}
        	}
		}

	private:
		
}; // end SomeClass

#endif
