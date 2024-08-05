##################
# SP2D_Utilities #
##################

cmake_minimum_required(VERSION 3.25)

project(sp2d-utils LANGUAGES CXX)

file(GLOB_RECURSE SP2DUTILS_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

add_library(${PROJECT_NAME} STATIC ${SP2DUTILS_SOURCES})
add_library(sp2d::utils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_logging/"
)
target_link_libraries(${PROJECT_NAME}
	PUBLIC "SDL2::SDL2-static"
	PUBLIC "sp2d::logging"
)

install(TARGETS ${PROJECT_NAME})