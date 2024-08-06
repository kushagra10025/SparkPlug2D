########
# SOL2 #
########

cmake_minimum_required(VERSION 3.25)

project(sol2)

add_library(${PROJECT_NAME} INTERFACE)

# No requirement of target_include_directories
#target_include_directories(${PROJECT_NAME}
#	INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
#)