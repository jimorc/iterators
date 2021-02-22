# iterators
This code in this repository creates a simple C++ value class and a custom C++ container class, including iterators, for objects of the value class. The value class and the container class are templated so that you can create value and container classes that hold different value types. 
See the article [Custom C++ Container Classes With Iterators](https://computingonplains.wordpress.com/custom-c-container-classes-with-iterators/) for a description of the various classes.

In addition to the templated classes, the project includes both a test program and unit tests using GoogleTest.

## Requirements
As a minimum:
* build tools including a C++17 compiler
* CMake
* internet access for downloading this repository and GoogleTest.

### Recommendations
* an IDE that supports C++.

All C++ IDEs either use CMake directly or convert CMake files into the IDE's build system files.

## Notes
### GoogleTest
The project in this repository uses GoogleTest for compiling and executing unit tests. You do not need to download, build, and install GoogleTest yourself. The CMakeLists.txt file in the tests directory downloads the GoogleTest master branch from GitHub, and GoogleTest will be built the first time you run a build.

### Compilers and Operating Systems
The project in this repository has been built on Windows 10 using MSVC and on Ubuntu 20.04 LTS using g++. As long as you use a system that supports the minimum requirements
that are listed above, you should have no trouble building this project.
