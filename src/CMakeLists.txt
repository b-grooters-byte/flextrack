cmake_minimum_required (VERSION 3.2)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)

# specify the include path
include_directories(
        include
        ${GTKMM_INCLUDE_DIRS} )

link_directories(
        ${GTKMM_LIBRARY_DIRS} )

add_library(FlexTrack
        Connector.cpp
        BezierCurve.cpp
        CurveView.cpp
        FlexTrackSegment.cpp
        Geometry.cpp
        TrackSegment.cpp)

target_link_libraries(
        FlexTrack
        ${GTKMM_LIBRARIES} )

target_compile_features(FlexTrack PRIVATE cxx_range_for)

add_executable(FlexTrackDemo Main.cpp)

target_compile_features(FlexTrackDemo PRIVATE cxx_range_for)

target_link_libraries (FlexTrackDemo FlexTrack)

