# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build

# Include any dependencies generated for this target.
include CMakeFiles/EPICALAnalysisObjectLib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/EPICALAnalysisObjectLib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/EPICALAnalysisObjectLib.dir/flags.make

CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o: CMakeFiles/EPICALAnalysisObjectLib.dir/flags.make
CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o: ../src/classes/EPICALAnalysisObject.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o -c /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/src/classes/EPICALAnalysisObject.cxx

CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/src/classes/EPICALAnalysisObject.cxx > CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.i

CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/src/classes/EPICALAnalysisObject.cxx -o CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.s

# Object files for target EPICALAnalysisObjectLib
EPICALAnalysisObjectLib_OBJECTS = \
"CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o"

# External object files for target EPICALAnalysisObjectLib
EPICALAnalysisObjectLib_EXTERNAL_OBJECTS =

libEPICALAnalysisObjectLib.dylib: CMakeFiles/EPICALAnalysisObjectLib.dir/src/classes/EPICALAnalysisObject.cxx.o
libEPICALAnalysisObjectLib.dylib: CMakeFiles/EPICALAnalysisObjectLib.dir/build.make
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libCore.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libImt.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libRIO.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libNet.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libHist.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGraf.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGraf3d.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGpad.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libROOTDataFrame.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libTree.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libTreePlayer.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libRint.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libPostscript.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMatrix.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libPhysics.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMathCore.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libThread.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMultiProc.so
libEPICALAnalysisObjectLib.dylib: libEPICALGeometryLib.dylib
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libCore.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libImt.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libRIO.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libNet.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libHist.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGraf.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGraf3d.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libGpad.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libROOTDataFrame.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libTree.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libTreePlayer.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libRint.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libPostscript.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMatrix.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libPhysics.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMathCore.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libThread.so
libEPICALAnalysisObjectLib.dylib: /usr/local/Cellar/root/6.22.02_2/lib/root/libMultiProc.so
libEPICALAnalysisObjectLib.dylib: CMakeFiles/EPICALAnalysisObjectLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libEPICALAnalysisObjectLib.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EPICALAnalysisObjectLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/EPICALAnalysisObjectLib.dir/build: libEPICALAnalysisObjectLib.dylib

.PHONY : CMakeFiles/EPICALAnalysisObjectLib.dir/build

CMakeFiles/EPICALAnalysisObjectLib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/EPICALAnalysisObjectLib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/EPICALAnalysisObjectLib.dir/clean

CMakeFiles/EPICALAnalysisObjectLib.dir/depend:
	cd /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build /Users/fpliquett/work/FoCal/analysiscode/EPICAL-Analysis-Project/build/CMakeFiles/EPICALAnalysisObjectLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/EPICALAnalysisObjectLib.dir/depend

