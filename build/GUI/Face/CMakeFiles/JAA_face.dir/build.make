# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/temp/source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/temp/source/build

# Include any dependencies generated for this target.
include GUI/Face/CMakeFiles/JAA_face.dir/depend.make

# Include the progress variables for this target.
include GUI/Face/CMakeFiles/JAA_face.dir/progress.make

# Include the compile flags for this target's objects.
include GUI/Face/CMakeFiles/JAA_face.dir/flags.make

GUI/Face/ui_face.h: ../GUI/Face/face.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/temp/source/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_face.h"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/uic -o /mnt/temp/source/build/GUI/Face/ui_face.h /mnt/temp/source/GUI/Face/face.ui

GUI/Face/moc_face.cxx: ../GUI/Face/face.h
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/temp/source/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating moc_face.cxx"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/moc -I/usr/include -I/usr/include/QtGui -I/usr/include/QtCore -DQT_GUI_LIB -DQT_CORE_LIB -o /mnt/temp/source/build/GUI/Face/moc_face.cxx /mnt/temp/source/GUI/Face/face.h

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o: GUI/Face/CMakeFiles/JAA_face.dir/flags.make
GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o: ../GUI/Face/face.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/temp/source/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JAA_face.dir/face.cpp.o -c /mnt/temp/source/GUI/Face/face.cpp

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JAA_face.dir/face.cpp.i"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/temp/source/GUI/Face/face.cpp > CMakeFiles/JAA_face.dir/face.cpp.i

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JAA_face.dir/face.cpp.s"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/temp/source/GUI/Face/face.cpp -o CMakeFiles/JAA_face.dir/face.cpp.s

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.requires:
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.requires

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.provides: GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.requires
	$(MAKE) -f GUI/Face/CMakeFiles/JAA_face.dir/build.make GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.provides.build
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.provides

GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.provides.build: GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o: GUI/Face/CMakeFiles/JAA_face.dir/flags.make
GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o: GUI/Face/moc_face.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/temp/source/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JAA_face.dir/moc_face.cxx.o -c /mnt/temp/source/build/GUI/Face/moc_face.cxx

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JAA_face.dir/moc_face.cxx.i"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/temp/source/build/GUI/Face/moc_face.cxx > CMakeFiles/JAA_face.dir/moc_face.cxx.i

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JAA_face.dir/moc_face.cxx.s"
	cd /mnt/temp/source/build/GUI/Face && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/temp/source/build/GUI/Face/moc_face.cxx -o CMakeFiles/JAA_face.dir/moc_face.cxx.s

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.requires:
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.requires

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.provides: GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.requires
	$(MAKE) -f GUI/Face/CMakeFiles/JAA_face.dir/build.make GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.provides.build
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.provides

GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.provides.build: GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o

# Object files for target JAA_face
JAA_face_OBJECTS = \
"CMakeFiles/JAA_face.dir/face.cpp.o" \
"CMakeFiles/JAA_face.dir/moc_face.cxx.o"

# External object files for target JAA_face
JAA_face_EXTERNAL_OBJECTS =

GUI/Face/libJAA_face.a: GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o
GUI/Face/libJAA_face.a: GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o
GUI/Face/libJAA_face.a: GUI/Face/CMakeFiles/JAA_face.dir/build.make
GUI/Face/libJAA_face.a: GUI/Face/CMakeFiles/JAA_face.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libJAA_face.a"
	cd /mnt/temp/source/build/GUI/Face && $(CMAKE_COMMAND) -P CMakeFiles/JAA_face.dir/cmake_clean_target.cmake
	cd /mnt/temp/source/build/GUI/Face && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JAA_face.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
GUI/Face/CMakeFiles/JAA_face.dir/build: GUI/Face/libJAA_face.a
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/build

GUI/Face/CMakeFiles/JAA_face.dir/requires: GUI/Face/CMakeFiles/JAA_face.dir/face.cpp.o.requires
GUI/Face/CMakeFiles/JAA_face.dir/requires: GUI/Face/CMakeFiles/JAA_face.dir/moc_face.cxx.o.requires
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/requires

GUI/Face/CMakeFiles/JAA_face.dir/clean:
	cd /mnt/temp/source/build/GUI/Face && $(CMAKE_COMMAND) -P CMakeFiles/JAA_face.dir/cmake_clean.cmake
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/clean

GUI/Face/CMakeFiles/JAA_face.dir/depend: GUI/Face/ui_face.h
GUI/Face/CMakeFiles/JAA_face.dir/depend: GUI/Face/moc_face.cxx
	cd /mnt/temp/source/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/temp/source /mnt/temp/source/GUI/Face /mnt/temp/source/build /mnt/temp/source/build/GUI/Face /mnt/temp/source/build/GUI/Face/CMakeFiles/JAA_face.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : GUI/Face/CMakeFiles/JAA_face.dir/depend
