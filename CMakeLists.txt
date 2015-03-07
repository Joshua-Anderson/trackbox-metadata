cmake_minimum_required(VERSION 2.8)

project("Trackbox Metadata")

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -static")
endif()

set(ENABLE_STATIC ON CACHE BOOL "Make static version of libtag")
set(ZLIB_SOURCE "${CMAKE_SOURCE_DIR}/lib/zlib" CACHE STRING "")
set(ENABLE_STATIC_RUNTIME ON CACHE BOOL "Visual Studio, link with runtime statically")
add_subdirectory("lib/zlib")
add_subdirectory("lib/taglib")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}"
										"${CMAKE_BINARY_DIR}/lib/taglib"
										"lib/taglib/taglib"
										"lib/taglib/taglib/toolkit"
										"lib/taglib/taglib/mpeg"
										"lib/taglib/taglib/mpeg/id3v1"
										"lib/taglib/taglib/mpeg/id3v2")

set(VERSION "Development")
configure_file(version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h)

add_executable(trackbox-metadata main.cpp)
target_link_libraries(trackbox-metadata tag)
