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
include CMakeFiles/JAA.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/JAA.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/JAA.dir/flags.make

CMakeFiles/JAA.dir/main.cpp.o: CMakeFiles/JAA.dir/flags.make
CMakeFiles/JAA.dir/main.cpp.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /mnt/temp/source/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/JAA.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/JAA.dir/main.cpp.o -c /mnt/temp/source/main.cpp

CMakeFiles/JAA.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/JAA.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /mnt/temp/source/main.cpp > CMakeFiles/JAA.dir/main.cpp.i

CMakeFiles/JAA.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/JAA.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /mnt/temp/source/main.cpp -o CMakeFiles/JAA.dir/main.cpp.s

CMakeFiles/JAA.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/JAA.dir/main.cpp.o.requires

CMakeFiles/JAA.dir/main.cpp.o.provides: CMakeFiles/JAA.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/JAA.dir/build.make CMakeFiles/JAA.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/JAA.dir/main.cpp.o.provides

CMakeFiles/JAA.dir/main.cpp.o.provides.build: CMakeFiles/JAA.dir/main.cpp.o

# Object files for target JAA
JAA_OBJECTS = \
"CMakeFiles/JAA.dir/main.cpp.o"

# External object files for target JAA
JAA_EXTERNAL_OBJECTS =

JAA: CMakeFiles/JAA.dir/main.cpp.o
JAA: CMakeFiles/JAA.dir/build.make
JAA: /usr/lib64/libQtGui.so
JAA: /usr/lib64/libQtCore.so
JAA: GUI/Face/libJAA_face.a
JAA: Compressor/libJAA_compressor.a
JAA: Compressor/Codec/libJAA_codec.a
JAA: GUI/CompressorThread/libJAA_ct.a
JAA: Compressor/libJAA_compressor.a
JAA: Compressor/Codec/libJAA_codec.a
JAA: Compressor/Codec/Codecs/BWT/libJAA_codec_bwt.a
JAA: Compressor/Codec/Codecs/BWT/divsuf/libJAA_divsuf.a
JAA: Compressor/Codec/Codecs/HUFF/libJAA_codec_huff.a
JAA: Compressor/Codec/Codecs/MTF/libJAA_codec_mtf.a
JAA: Compressor/Codec/Codecs/RLE/libJAA_codec_rle.a
JAA: Compressor/DataBlock/libJAA_datablock.a
JAA: Compressor/FilesTable/libJAA_filestable.a
JAA: Compressor/CRC/libJAA_crc.a
JAA: GUI/FileList/libJAA_filelist.a
JAA: GUI/SettingsPanels/libJAA_settings_panel.a
JAA: GUI/StatInfoW/libJAA_stw.a
JAA: GUI/DataUnitsToQString/libJAA_dus.a
JAA: /usr/lib64/libQtGui.so
JAA: /usr/lib64/libQtCore.so
JAA: CMakeFiles/JAA.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable JAA"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/JAA.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/JAA.dir/build: JAA
.PHONY : CMakeFiles/JAA.dir/build

CMakeFiles/JAA.dir/requires: CMakeFiles/JAA.dir/main.cpp.o.requires
.PHONY : CMakeFiles/JAA.dir/requires

CMakeFiles/JAA.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/JAA.dir/cmake_clean.cmake
.PHONY : CMakeFiles/JAA.dir/clean

CMakeFiles/JAA.dir/depend:
	cd /mnt/temp/source/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/temp/source /mnt/temp/source /mnt/temp/source/build /mnt/temp/source/build /mnt/temp/source/build/CMakeFiles/JAA.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/JAA.dir/depend

