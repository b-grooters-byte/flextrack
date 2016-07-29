cmake_minimum_required (VERSION 3.2)

project(FlexTrackDemo)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

#include path
include_directories(
    ${GTKMM_INCLUDE_DIRS} 	   
    ${FlexTrackLib_SOURCE_DIR}/include
)

# link path 
link_directories(
        ${GTKMM_LIBRARY_DIRS} 
)

add_executable(
    FlexTrackDemo
	
	main.cpp
)

#
# Libraries required to build the demo app
#
target_link_libraries (
    FlexTrackDemo FlexTrackLib ${GTKMM_LIBRARIES}
)