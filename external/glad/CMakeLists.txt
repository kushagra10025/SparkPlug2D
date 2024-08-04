########
# GLAD #
########

cmake_minimum_required(VERSION 3.25)

project(glad)

set(GLAD_SOURCES "src/glad.c")

find_package(OpenGL REQUIRED)

add_library(${PROJECT_NAME} STATIC ${GLAD_SOURCES})
add_library(glad::glad ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC OpenGL::GL
)

install(TARGETS ${PROJECT_NAME})