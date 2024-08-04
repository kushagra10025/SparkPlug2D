###############
# SP2D_Editor #
###############

cmake_minimum_required(VERSION 3.25)

project(sp2d-editor)

file(GLOB_RECURSE SP2DEDITOR_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

add_executable(${PROJECT_NAME} ${SP2DEDITOR_SOURCES})

# TODO Add Target Include Directories
# TODO Add Target Link Libraries

install(TARGETS ${PROJECT_NAME})