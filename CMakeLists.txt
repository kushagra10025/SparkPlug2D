########
# ROOT #
########

cmake_minimum_required(VERSION 3.25)

project(SparkPlug2D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SP2D_ENABLE_EDITOR "Build the SparkPlug2D Editor!" ON)

add_subdirectory("external/glad")

add_subdirectory("sp2d_core")
add_subdirectory("sp2d_utilities")
add_subdirectory("sp2d_windowing")

if(${SP2D_ENABLE_EDITOR})
	add_subdirectory("sp2d_editor")
endif()