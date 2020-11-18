# Install script for directory: /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELWITHDEBINFO")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/test")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install" TYPE EXECUTABLE FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/test")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/test" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/test")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build"
      "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/test")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/test")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/produce_all")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install" TYPE EXECUTABLE FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/produce_all")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/produce_all" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/produce_all")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build"
      "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/produce_all")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/produce_all")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_pixelmaskoverview")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install" TYPE EXECUTABLE FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/draw_pixelmaskoverview")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_pixelmaskoverview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_pixelmaskoverview")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build"
      "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_pixelmaskoverview")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_pixelmaskoverview")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_hitmapoverview")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install" TYPE EXECUTABLE FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/draw_hitmapoverview")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_hitmapoverview" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_hitmapoverview")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build"
      "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_hitmapoverview")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -u -r "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/install/draw_hitmapoverview")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libmyStyleLib.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib" TYPE SHARED_LIBRARY FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/libmyStyleLib.dylib")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libmyStyleLib.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libmyStyleLib.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libmyStyleLib.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALAnalysisObjectLib.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib" TYPE SHARED_LIBRARY FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/libEPICALAnalysisObjectLib.dylib")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALAnalysisObjectLib.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALAnalysisObjectLib.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build"
      "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALAnalysisObjectLib.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALAnalysisObjectLib.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALGeometryLib.dylib")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib" TYPE SHARED_LIBRARY FILES "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/libEPICALGeometryLib.dylib")
  if(EXISTS "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALGeometryLib.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALGeometryLib.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" -x "$ENV{DESTDIR}/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/lib/libEPICALGeometryLib.dylib")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
