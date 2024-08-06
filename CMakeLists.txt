########
# ROOT #
########

cmake_minimum_required(VERSION 3.25)

project(SparkPlug2D LANGUAGES CXX C)

# Set Project Properties

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Custom Options
option(SP2D_ENABLE_EDITOR "Build the SparkPlug2D Editor!" ON)

# External Libraries
add_subdirectory("external/glad")
add_subdirectory("external/SDL")
add_subdirectory("external/SOIL2")
add_subdirectory("external/glm")
add_subdirectory("external/spdlog")
add_subdirectory("external/entt")
add_subdirectory("external/lua")
add_subdirectory("external/sol2")

# Internal Libraries
add_subdirectory("sp2d_core")
add_subdirectory("sp2d_utilities")
add_subdirectory("sp2d_windowing")
add_subdirectory("sp2d_rendering")
add_subdirectory("sp2d_logging")

if(${SP2D_ENABLE_EDITOR})
	add_subdirectory("sp2d_editor")
endif()

# Targets Variables for set_target_properties
set(EXTERNAL_TARGETS "glad" "soil2" "glm" "spdlog")
set(EXTERNAL_TARGETS_SDL "SDL2" "SDL2main" "SDL2_test" "SDL2-static" "sdl_headers_copy" "uninstall")
set(INTERNAL_TARGETS "sp2d-core" "sp2d-utils" "sp2d-windowing" "sp2d-editor" "sp2d-rendering" "sp2d-logging")

set_target_properties(${EXTERNAL_TARGETS} PROPERTIES FOLDER "external")
set_target_properties(${EXTERNAL_TARGETS_SDL} PROPERTIES FOLDER "external/SDL")
set_target_properties(${INTERNAL_TARGETS} PROPERTIES FOLDER "internal")

