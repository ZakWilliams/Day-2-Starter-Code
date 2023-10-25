#Set CMake requirements and declare project
cmake_minimum_required(VERSION 3.2)
project(MPAGSCipher VERSION 0.1.0)

#When makefiles generated, output all command lines by default
#do this to begin with so it's easy to see what compiler 
#command/flags are used. This can be done by removing the 
#'set' command and running make as make as 'make VERBOSE=1'
set(CMAKE_VERBOSE_MAKEFILE ON)

#Set cmake standard directly
set(CMAKE_CXX_STANDARD 14)

#Declare build of mapgs-cipher main program
add_executable(mpags-cipher
    mpags-cipher.cpp
    MPAGSCipher/TransformChar.cpp
    MPAGSCipher/ProcessCommandLine.cpp
    )

#Using standard set of flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -Wshadow -pedantic")

#Compile features and flags
target_compile_features(mpags-cipher
    PRIVATE cxx_auto_type cxx_range_for cxx_uniform_initialization
    )

#Don't allow all C++ compiler vendor extensions
set(CMAKE_CXX_EXTENSIONS OFF)