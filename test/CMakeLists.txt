cmake_minimum_required (VERSION 3.2)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (
   ${FlexTrack_SOURCE_DIR}/src/include
   ${Boost_INCLUDE_DIRS}
)

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable (UnitTest GeometryTest.cpp)

target_link_libraries(
    UnitTest
    FlexTrack
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(MyTest test)

target_compile_features(UnitTest PRIVATE cxx_range_for)
