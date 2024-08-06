#######
# LUA #
#######

cmake_minimum_required(VERSION 3.25)

project(lua)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	message(STATUS "[LUA] Settings the Lua Static Lib - Built for Windows MSVC16")
	set(LUA_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/lib/lua53.lib")
else()
	# TODO Add Lua Static Library for LINUX
	message(FATAL_ERROR "Lua Library files for OS other than Windows not available now!!")
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(lua::lua ALIAS ${PROJECT_NAME})

# No requirement of target_include_directories
#target_include_directories(${PROJECT_NAME}
#	INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include"
#)

target_link_libraries(${PROJECT_NAME}
	INTERFACE ${LUA_LIBS}
)

# Install the Lua.lib file to appropriate location
install(FILES ${LUA_LIBS} DESTINATION "lib/")