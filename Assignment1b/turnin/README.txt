My program takes in a text file and outputs a ppm image.
It reads imsize (image size) and outputs a ppm image of that size with alternating red, blue, and green pixels.
It parses the text file and creates property tuples consisting of a name of the property (such as image size) 
and the properties (such as width and height). I can read these properties from the tuples to create my image.
Comments, blank lines, extranious properties are ignored.