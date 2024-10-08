###############
# SP2D_Editor #
###############

cmake_minimum_required(VERSION 3.25)

project(sp2d-editor LANGUAGES CXX)

file(GLOB_RECURSE SP2DEDITOR_SOURCES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

find_package(OpenGL)

add_executable(${PROJECT_NAME} ${SP2DEDITOR_SOURCES})

target_include_directories(${PROJECT_NAME}
	PUBLIC "${CMAKE_SOURCE_DIR}/external/glad/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/SDL/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/SOIL2/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/glm"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/entt/src"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/lua/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/external/sol2/include"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_core/"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_utilities/"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_windowing/"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_rendering/"
	PUBLIC "${CMAKE_SOURCE_DIR}/sp2d_logging/"
)
target_link_libraries(${PROJECT_NAME}
	PUBLIC "OpenGL::GL"
	PUBLIC "glad::glad"
	PUBLIC "SDL2::SDL2main"
	PUBLIC "SDL2::SDL2-static"
	PUBLIC "soil2"
	PUBLIC "glm::glm"
	PUBLIC "EnTT::EnTT"
	PUBLIC "lua::lua"
	PUBLIC "sp2d::core"
	PUBLIC "sp2d::utils"
	PUBLIC "sp2d::windowing"
	PUBLIC "sp2d::rendering"
	PUBLIC "sp2d::logging"
)

# Installations
install(TARGETS ${PROJECT_NAME})
# Install the Assets Folder to appropriate location
install(DIRECTORY "assets/" DESTINATION "bin/assets")