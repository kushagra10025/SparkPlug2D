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

target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/glm"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/entt/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/lua/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sol2/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_rendering/"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_logging/"
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC "SDL2::SDL2-static"
	PUBLIC "glm::glm"
	PUBLIC "EnTT::EnTT"
	PUBLIC "lua::lua"
	PUBLIC "sp2d::rendering"
	PUBLIC "sp2d::logging"
)

install(TARGETS ${PROJECT_NAME})