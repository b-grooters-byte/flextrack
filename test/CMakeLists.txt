cmake_minimum_required (VERSION 3.2)


find_package(Boost
             COMPONENTS system filesystem unit_test_framework
			 REQUIRED)

include_directories (
   ${FlexTrack_SOURCE_DIR}/src/include
   ${Boost_INCLUDE_DIRS}
)

add_definitions(-DBOOST_TEST_DYN_LINK)


file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(TEST_SRC ${TEST_SRCS})
    # get the filename without extension
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)
	
    add_executable (${TEST_NAME} ${TEST_SRC})
    target_link_libraries(
        ${TEST_NAME}
        FlexTrack
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

    add_test(${TEST_NAME} ${TEST_NAME})
	
    target_compile_features(${TEST_NAME} PRIVATE cxx_range_for)
	
endforeach(TEST_SRC)



