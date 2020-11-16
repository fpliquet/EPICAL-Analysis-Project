cmake_minimum_required(VERSION 3.16)
project(EPICALProject CXX)
add_executable(test src/macros/test.cxx)
add_executable(Init src/macros/Init.cxx)
add_executable(draw_pixelmaskoverview src/macros/draw_pixelmaskoverview.cxx)
add_executable(draw_hitmapoverview src/macros/draw_hitmapoverview.cxx)


add_library(testLib SHARED include/testClass.h src/classes/testClass.cxx)
add_library(mystylelib SHARED /Users/fpliquett/commoncode/myStyle.h /Users/fpliquett/commoncode/myStyle.cxx)
add_library(EPICALAnalysisObjectLib SHARED include/EPICALAnalysisObject.h src/classes/EPICALAnalysisObject.cxx)
add_library(EPICALGeometryLib SHARED include/EPICALGeometry.h src/classes/EPICALGeometry.cxx)


find_package(ROOT)
if(ROOT_FOUND)
  include(${ROOT_USE_FILE})
  message(STATUS "root  version: ${ROOT_VERSION}")
  target_link_libraries(testLib ${ROOT_LIBRARIES})
  target_link_libraries(mystylelib ${ROOT_LIBRARIES})
  target_link_libraries(EPICALAnalysisObjectLib ${ROOT_LIBRARIES})
  target_link_libraries(EPICALGeometryLib ${ROOT_LIBRARIES})
else()
  message(ERROR "Could not find root")
endif(ROOT_FOUND)

target_link_libraries(EPICALAnalysisObjectLib EPICALGeometryLib)
target_link_libraries(test testLib)
target_link_libraries(test mystylelib)
target_link_libraries(test EPICALAnalysisObjectLib)
target_link_libraries(test EPICALGeometryLib)

target_link_libraries(Init EPICALAnalysisObjectLib)
target_link_libraries(draw_pixelmaskoverview EPICALAnalysisObjectLib)
target_link_libraries(draw_hitmapoverview EPICALAnalysisObjectLib)

install(TARGETS test
  RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/install
)
install(TARGETS testLib
  LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
install(TARGETS mystylelib
  LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
install(TARGETS EPICALAnalysisObjectLib
  LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)
install(TARGETS EPICALGeometryLib
  LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
)


# use, i.e. don't skip the full RPATH for the build tree
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
# set(CMAKE_INSTALL_RPATH "/Users/fpliquett/work/FoCal/analysiscode/EPICALProject/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
list(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
if("${isSystemDir}" STREQUAL "-1")
    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif("${isSystemDir}" STREQUAL "-1")


# by default build optimized code with debug symbols
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RELWITHDEBINFO)
endif()

set(CMAKE_ALLOWED_BUILD_TYPES DEBUG RELEASE RELWITHDEBINFO)
if(NOT CMAKE_BUILD_TYPE IN_LIST CMAKE_ALLOWED_BUILD_TYPES)
  message(FATAL_ERROR "Invalid build type ${CMAKE_BUILD_TYPE}. Use one of: ${CMAKE_ALLOWED_BUILD_TYPES}.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -DDEBUG -D__DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ftree-vectorize -ffast-math -DNODEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -ggdb")
message(STATUS "Using CXX flags for ${CMAKE_BUILD_TYPE}: ${CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}}")

#C++ standards
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# message(STATUS "Using C++${CMAKE_CXX_STANDARD}")
#
# enable_testing()
# add_test(simpleTest testExe)
