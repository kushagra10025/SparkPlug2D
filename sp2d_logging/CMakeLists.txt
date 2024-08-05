################
# SP2D_Logging #
################

cmake_minimum_required(VERSION 3.25)

project(sp2d-logging LANGUAGES CXX)

file(GLOB_RECURSE SP2DLOGGING_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

add_library(${PROJECT_NAME} STATIC ${SP2DLOGGING_SOURCES})
add_library(sp2d::logging ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/spdlog/include"
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC "spdlog::spdlog"
)

target_compile_definitions(${PROJECT_NAME}
	PUBLIC "SP2D_SOURCE_DETAILS_LOG=1"
)

install(TARGETS ${PROJECT_NAME})