cmake_minimum_required(VERSION 2.6)
if(MSVC)
	set(CMAKE_GENERATOR_PLATFORM Win32)
endif()
project(Arcade_Renderer)

add_subdirectory(CoBeBeEngine)

include_directories(
	src
	include
	CoBeBeEngine/src
	CoBeBeEngine/include/common
	CoBeBeEngine/include/msvc
)

add_executable(arcade_renderer
	src/arcade/Cabinet.h
	src/arcade/Cabinet.cpp
	src/arcade/main.cpp
)

target_link_libraries(arcade_renderer
	cobebe
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")	
	set(CMAKE_EXECUTABLE_SUFFIX ".html")

	set_target_properties(arcade_renderer PROPERTIES LINK_FLAGS  
	"--preload-file Resources -s MIN_WEBGL_VERSION=2 -s USE_SDL=2 -s USE_WEBGL2=1 -s DISABLE_EXCEPTION_CATCHING=0 -s ALLOW_MEMORY_GROWTH=1 --no-heap-copy")
endif()