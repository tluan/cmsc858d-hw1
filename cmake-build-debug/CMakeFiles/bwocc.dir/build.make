# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kmirai/Projects/858d

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kmirai/Projects/858d/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/bwocc.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bwocc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bwocc.dir/flags.make

CMakeFiles/bwocc.dir/bwocc.cpp.o: CMakeFiles/bwocc.dir/flags.make
CMakeFiles/bwocc.dir/bwocc.cpp.o: ../bwocc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kmirai/Projects/858d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bwocc.dir/bwocc.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bwocc.dir/bwocc.cpp.o -c /Users/kmirai/Projects/858d/bwocc.cpp

CMakeFiles/bwocc.dir/bwocc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bwocc.dir/bwocc.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kmirai/Projects/858d/bwocc.cpp > CMakeFiles/bwocc.dir/bwocc.cpp.i

CMakeFiles/bwocc.dir/bwocc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bwocc.dir/bwocc.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kmirai/Projects/858d/bwocc.cpp -o CMakeFiles/bwocc.dir/bwocc.cpp.s

# Object files for target bwocc
bwocc_OBJECTS = \
"CMakeFiles/bwocc.dir/bwocc.cpp.o"

# External object files for target bwocc
bwocc_EXTERNAL_OBJECTS =

bwocc: CMakeFiles/bwocc.dir/bwocc.cpp.o
bwocc: CMakeFiles/bwocc.dir/build.make
bwocc: CMakeFiles/bwocc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kmirai/Projects/858d/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bwocc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bwocc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bwocc.dir/build: bwocc

.PHONY : CMakeFiles/bwocc.dir/build

CMakeFiles/bwocc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bwocc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bwocc.dir/clean

CMakeFiles/bwocc.dir/depend:
	cd /Users/kmirai/Projects/858d/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kmirai/Projects/858d /Users/kmirai/Projects/858d /Users/kmirai/Projects/858d/cmake-build-debug /Users/kmirai/Projects/858d/cmake-build-debug /Users/kmirai/Projects/858d/cmake-build-debug/CMakeFiles/bwocc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bwocc.dir/depend

