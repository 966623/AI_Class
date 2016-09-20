#ifndef SOMECLASS_HPP
#define SOMECLASS_HPP

#include <sstream> // stringstreams

class Vec2f {
public:
	Vec2f() : x(0), y(0) {}
	Vec2f( float x_, float y_ ) : x(x_), y(y_) {}
	float x, y;
	std::string to_str();
}; // end SomeClass

#endif
