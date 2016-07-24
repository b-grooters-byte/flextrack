cmake_minimum_required (VERSION 3.2)

project (FlexTrack)

# set the version number
set (FlexTrack_VERSION_MAJOR 0)
set (FlexTrack_VERSION_MINOR 1)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME GeometryTest COMMAND GeometryTest)
add_test(NAME BezierTest COMMAND BezierTest)


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


