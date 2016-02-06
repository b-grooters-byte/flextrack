cmake_minimum_required (VERSION 3.2)

project (FlexTrack)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)


# set the version number
set (FlexTrack_VERSION_MAJOR 0)
set (FlexTrack_VERSION_MINOR 1)

# specify the include path
include_directories(
    include
    ${GTKMM_INCLUDE_DIRS} )

link_directories(
    ${GTKMM_LIBRARY_DIRS} )


# include all sources
file(GLOB SOURCES "src/*.cpp")

add_executable (FlexTrack ${SOURCES})

target_link_libraries(
    FlexTrack
    ${GTKMM_LIBRARIES} )

target_compile_features(FlexTrack PRIVATE cxx_range_for)
