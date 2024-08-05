##################
# SP2D_Rendering #
##################

cmake_minimum_required(VERSION 3.25)

project(sp2d-rendering LANGUAGES CXX)

file(GLOB_RECURSE SP2DRENDERING_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

find_package(OpenGL)

add_library(${PROJECT_NAME} STATIC ${SP2DRENDERING_SOURCES})
add_library(sp2d::rendering ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/glad/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/SOIL2/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/glm"
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC "OpenGL::GL"
	PUBLIC "glad::glad"
	PUBLIC "soil2"
	PUBLIC "glm::glm"
)

install(TARGETS ${PROJECT_NAME})