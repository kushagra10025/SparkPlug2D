#############
# SP2D_Core #
#############

cmake_minimum_required(VERSION 3.25)

project(sp2d-core LANGUAGES CXX)

file(GLOB_RECURSE SP2DCORE_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

add_library(${PROJECT_NAME} STATIC ${SP2DCORE_SOURCES})
add_library(sp2d::core ALIAS ${PROJECT_NAME})

# TODO Add Target Include Directories
# TODO Add Target Link Libraries

install(TARGETS ${PROJECT_NAME})