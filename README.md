# Cpp-FileSystem-Emulator
[![TraviCI](https://api.travis-ci.com/p-hofmann/Cpp-FileSystem-Emulator.svg?branch=master)](https://travis-ci.com/p-hofmann/CPP-Template-Sub1-Sub)
[![CircleCI](https://circleci.com/gh/p-hofmann/Cpp-FileSystem-Emulator/tree/master.svg?style=svg)](https://circleci.com/gh/p-hofmann/CPP-Template-Sub1-Sub/tree/master)  
Emulator of 'std::filesystem' 
Emulates '<experimental/filesystem>' without the need for g++17.
It is usable with g++11 without additional libraries
 * Early version: Not all methods are implemented since they are coded as they are needed.
 * Additional methods are available, such as get_full_path().
 * Compatible with Linux, Windows OS and Apple(Darwin).
 * Continuous integration: [Circle CI](https://circleci.com/), [Circle CI](https://circleci.com/).
 
 ├── CMakeLists.txt  
 ├── .travis.yml  
 ├── include  
 │&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── filesystem.h  
 ├── src  
 │&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── filesystem_LINUX.cpp  
 │&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── filesystem_WIN32.cpp  
 ├── external  
 │&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── catch2  
 │&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── catch.hpp  
 └── tests  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── CMakeLists.txt  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;├── test_filesystem_LINUX.cpp  
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── test_filesystem_WIN32.cpp  

* [Catch2](https://github.com/catchorg/Catch2) will be downloaded as part of cmake when run on unittests