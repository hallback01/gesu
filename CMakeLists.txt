# compile to a universal library when compiling for mac os
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

cmake_minimum_required(VERSION 3.16.3)
project(gesu CXX)
set(CMAKE_CXX_STANDARD 17)

#add include directory
include_directories(${PROJECT_SOURCE_DIR}/include/)

# add source files
file(GLOB_RECURSE src_files "src/*.cpp")
file(GLOB_RECURSE include_files "include/*.h")

#create lib
add_library(gesu STATIC ${src_files} ${include_files})
