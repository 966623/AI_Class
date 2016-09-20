
//
//	To run this example, pass a text file as an argument.
//	e.g. "./example ../examplefile.txt"
//

#include "SomeClass.hpp"
#include <vector>
#include <iostream> // cout and cerr
#include <fstream> // file streams
#include <sstream> // stringstreams

int main( int argc, char **argv ){

	// Make sure the user specified an input file. If not, tell them how to do so.
	if( argc < 2 ){ std::cerr << "**Error: you must specify an input file, " <<
		"e.g. \"./example ../examplefile.txt\"" << std::endl; return 0; }

	// We'll store the list of objects parsed from the text file in std::vectors.
	std::vector< Vec2f > list_of_vec2f;
	std::vector< float > list_of_floats;
	std::vector< std::string > list_of_strings;

	// Get the input text file, which should be the second argument.
	std::string filename( argv[1] );
	std::cout << "Input file: " << filename << std::endl;

	// Create a filestream for reading the text file, and open it.
	// The is_open call will return false if there was a problem.
	std::ifstream inputfile( filename.c_str() );
	if( inputfile.is_open() ){

		// Use std::getline to parse the text file one line at a time.
		std::string line="";
		while( std::getline( inputfile, line ) ){

			// At this point, "line" contains the full text of the parsed line.
			// We can use a stringstream to parse out the space-delimited contents of the line
			std::stringstream ss( line );

			// Using the stream operator, get the first string of the line.
			// It will decide how we parse the rest of it.
			std::string var="";
			ss >> var;

			// Was it a vector?
			if( var == "aVector" ){
				float x=0.f, y=0.f;
				ss >> x >> y;
				list_of_vec2f.push_back( Vec2f(x,y) ); // Add it to our list
			}

			// How about a string?
			else if( var == "aString" ){
				std::string str = "";
				ss >> str;
				list_of_strings.push_back( str ); // Add it to the list
			}

			// Maybe a float...
			else if( var == "aFloat" ){
				float f;
				ss >> f;
				list_of_floats.push_back( f ); // Add it to the list
			}

			// If it's a comment, don't do anything.
			else if( var == "#" ){}

			// Otherwise, it's an error!
			else { std::cerr << "**Error: I don't know what \"" << var << "\" is! " << std::endl; }

		} // end parse line

	}
	else { std::cerr << "**Error: Could not open file " << filename << std::endl; return 0; }

	// Just for verification, we'll print out the stuff we parse:
	std::cout << "Vectors parsed from the file: " << std::endl;
	for( int i=0; i<list_of_vec2f.size(); ++i ){ std::cout << "\t" << i+1 << ") " << list_of_vec2f[i].to_str() << std::endl; }
	std::cout << "Strings parsed from the file: " << std::endl;
	for( int i=0; i<list_of_strings.size(); ++i ){ std::cout << "\t" << i+1 << ") " << list_of_strings[i] << std::endl; }
	std::cout << "Floats parsed from the file: " << std::endl;
	for( int i=0; i<list_of_floats.size(); ++i ){ std::cout << "\t" << i+1 << ") " << list_of_floats[i] << std::endl; }

	// All done.
	return 0;

} // end main
