cmake_minimum_required (VERSION 3.2)

project (FlexTrack)

# set the version number
set (FlexTrack_VERSION_MAJOR 0)
set (FlexTrack_VERSION_MINOR 1)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME TestTest COMMAND UnitTest)

