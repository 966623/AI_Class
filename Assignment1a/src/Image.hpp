#ifndef Image_HPP
#define Image_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include <fstream>
#include "Vec3.hpp"

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

		Image (int w, int h, Vec3 b){
			height = h;
			width = w;
			bkg = b;
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
