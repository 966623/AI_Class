File parsing with C++ [stringstreams](http://www.cplusplus.com/reference/sstream/stringstream/) and building a project with [CMake](https://cmake.org/).

This example code was created for CSci 5607 at the University of Minnesota.

## What is CMake?

[CMake](https://cmake.org/) stands for cross-platform make. It is an incredibly useful tool for compiling code
across all platforms, with support for IDEs such as [Xcode and Visual Studio](https://cmake.org/cmake/help/v2.8.0/cmake.html#section_Generators). It doesn't do the actual compilation. Instead, it generates native build files for whatever platform you're compiling on.

To see how it works, open up CMakeLists.txt.

## Installing CMake

The CS dev machines already have CMake installed. If you want to install it on your own computer:

Ubuntu:

    sudo apt-get install cmake

On Mac, I recommend installing with [Homebrew](http://brew.sh). This gives you access to the command-line tools, which are much easier to use than the CMake gui.

    brew install cmake

On Windows: [Download/install the binaries](https://cmake.org/download)


## How do I use CMake?

It's best to execute cmake from another directory. In the linux or mac terminal ([if you installed CMake with Homebrew](http://brewformulas.org/Cmake)) we can do:

    mkdir build
    cd build
    cmake ..

After that, a Makefile will be generated in the build directory. Note that the ".." specifies the directory that contains our CMakeLists.txt. If you're running CMake from a different directory, that argument will be different. Then, we can build our project with:

    make -j

At this point, only "make -j" is required to compile new changes.

## How do I use CMake with Xcode or Visual Studio?

Instead of using the cmake .. command above, use: 

    cmake .. -G Xcode

or

    cmake .. -G "Visual Studio 10"

which will generate your .xcodeproj or .sln file. If you are going to use VS or Xcode, be sure to keep your CMakeLists.txt file updated when you add new files!


## File List:

* CMakeLists.txt: The CMake file that will generate the make files. See "What is CMake" above.
* src/main.cpp: The source file containing int main(...)
* src/SomeClass.hpp: The C++ header file of a class called "Vec2f"
* src/SomeClass.cpp: The C++ implementation file of a class called "Vec2f"
