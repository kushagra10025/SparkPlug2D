##################
# SP2D_Windowing #
##################

cmake_minimum_required(VERSION 3.25)

project(sp2d-windowing)

file(GLOB_RECURSE SP2DWINDOWING_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

add_library(${PROJECT_NAME} STATIC ${SP2DWINDOWING_SOURCES})
add_library(sp2d::windowing ALIAS ${PROJECT_NAME})

# TODO Add Target Include Directories
# TODO Add Target Link Libraries

install(TARGETS ${PROJECT_NAME})