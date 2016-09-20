#ifndef Image_HPP
#define Image_HPP

#include <tuple>
#include <vector>
#include <sstream>
#include <math.h>
#include "Vec3.hpp"

using namespace std;

class Image {
	public:

		int height;
		int width;
		Vec3 bkg;
		Image (){

		}

		Image (int w, int h, Vec3 b){
			height = h;
			width = w;
			bkg = b;
		}

	private:
		
}; // end SomeClass

#endif
