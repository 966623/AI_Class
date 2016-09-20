#include "SomeClass.hpp"

std::string Vec2f::to_str(){
	// We can also use stringstreams to cast numbers back into strings!
	std::stringstream ss;
	ss << x << ' ' << y;
	return ss.str();
}
