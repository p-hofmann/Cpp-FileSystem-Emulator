# Cpp-FileSystem-Emulator
Emulator of 'std::filesystem' 
Emulates '<experimental/filesystem>' without the need for g++17.
It is usable with g++11 without additional libraries
 * Prototype: Not all methods are implemented as they are made as they are needed.
 * Additional methods are available, such as get_full_path().
 * Compatible with Linux and Windows OS.
 
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

* Catch2 will be downloaded as part of cmake when run on unittests