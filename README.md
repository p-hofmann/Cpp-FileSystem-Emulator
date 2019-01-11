# Cpp-FileSystem-Emulator
[![TraviCI](https://api.travis-ci.com/p-hofmann/Cpp-FileSystem-Emulator.svg?branch=master)](https://travis-ci.com/p-hofmann/Cpp-FileSystem-Emulator)
[![CircleCI](https://circleci.com/gh/p-hofmann/Cpp-FileSystem-Emulator/tree/master.svg?style=svg)](https://circleci.com/gh/p-hofmann/Cpp-FileSystem-Emulator/tree/master)  
Emulates '<experimental/filesystem>' without the need for g++17.
It is usable with g++11 without additional libraries
 * Early version: Not all methods are implemented since they are coded as they are needed.
 * Additional methods are available, such as force_absolute_path().
 * Compatible with Linux, Windows OS and Apple(Darwin).
 * Continuous integration: [Circle CI](https://circleci.com/), [Circle CI](https://circleci.com/).
 
## Noteworthy methods
All methods are compatible with Linux, Windows OS and Apple(Darwin).

### filesystem::path::force_absolute_path()
This methods forces an absolute path from a given file or folder path.  
Given a relative path, the current working directory is added, 
except in case it is an executable found in the system path.
In such a case the system path is added. 
Using Windows OS, the extension '.exe' might be added 
if an executable(.exe) file was found in the system path.
Note however, that an extension will not be looked for in any other case!
If a local relative directory/file and a system path file fit a given relative path, 
the local path is given priority.  
A file or folder does not need to exist for a path to get transformed into a full path, it only effects priority.  
Priority: Existing local path > System file > Local path   

### filesystem::get_environment_variable(your_variable)
Resolves a environment variable and returns it as string.

### filesystem::current_path()
Get the current working directory! 

## Project Layout
 
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

## TODO
* Valgrind test in Windows OS
* Recreate missing methods from original filesystem
* UTF-8 support for paths