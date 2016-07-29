cmake_minimum_required (VERSION 3.2)

project(FlexTrackLib)

if (DEFINED ${FlexTrack_VERSION_MAJOR})
    set(FlexTrackLib_VERSION_MAJOR ${FlexTrack_VERSION_MAJOR})
else(DEFINED ${FlexTrack_VERSION_MAJOR})
    set(FlexTrackLib_VERSION_MAJOR 0)
endif(DEFINED ${FlexTrack_VERSION_MAJOR})

if (DEFINED ${FlexTrack_VERSION_MINOR})
    set(FlexTrackLib_VERSION_MINOR ${FlexTrack_VERSION_MINOR})
else(DEFINED ${FlexTrack_VERSION_MINOR})
    set(FlexTrackLib_VERSION_MINOR 1)
endif(DEFINED ${FlexTrack_VERSION_MINOR})

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  include/FlexTrackLibConfig.h.in
  ${PROJECT_BINARY_DIR}/include/FlexTrackLibConfig.h
)

# specify the include path
include_directories(
        include
		${PROJECT_BINARY_DIR}/include
        ${GTKMM_INCLUDE_DIRS} 	   
)

# link path 
link_directories(
        ${GTKMM_LIBRARY_DIRS} 
)

add_library(
    FlexTrackLib 
	
    # cpp files for library
	Geometry.cpp
	BezierCurve.cpp
	Connector.cpp
	CurveView.cpp
	TrackSegment.cpp
	FlexTrackSegment.cpp
	CurveView.cpp
	
	# header files included here for code::blocks project generator
	include/BezierCurve.h
	include/Connector.h
	include/CurveView.h
	include/FlexTrackSegment.h
	include/Geometry.h
	include/NScale.h
	include/TrackSegment.h	
)

target_link_libraries(
        FlexTrackLib
        ${GTKMM_LIBRARIES} 
)

# C++11 support
target_compile_features(FlexTrackLib PRIVATE cxx_constexpr)
target_compile_features(FlexTrackLib PRIVATE cxx_range_for)

if("${BUILD_ARCH}" STREQUAL "x86_64")
    message("64bit build")
    set(CMAKE_CXX_FLAGS "-Wall -m64")
endif("${BUILD_ARCH}" STREQUAL "x86_64")

#
# Unit Tests
#
find_package(
        Boost
        COMPONENTS system filesystem unit_test_framework
        REQUIRED
)
enable_testing()
add_definitions(-DBOOST_TEST_DYN_LINK)
file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)
foreach(TEST_SRC ${TEST_SRCS})
    # get the filename without the extension
	get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
    
	add_executable (${TEST_NAME} ${TEST_SRC})
    
	target_link_libraries(
        ${TEST_NAME}
        FlexTrackLib
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )
	
	set_target_properties(
	    ${TEST_NAME} PROPERTIES 
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/test
	)
	
    add_test(
	    NAME ${TEST_NAME} 
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/test/${TEST_NAME}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/test		
	)
	
	# C++11 range for support
    target_compile_features(${TEST_NAME} PRIVATE cxx_range_for)

endforeach(TEST_SRC)

#
# Doxygen API documentation
#
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/doc)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc)
endif(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/doc)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
  if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(
      doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

#
# INSTALLATION
#
install (
    FILES FlexTrackLib DESTINATION bin 	
)



