# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/zyf/miniconda3/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/zyf/miniconda3/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zyf/Homework/GreedySnake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zyf/Homework/GreedySnake/build

# Include any dependencies generated for this target.
include CMakeFiles/test_snake.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_snake.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_snake.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_snake.dir/flags.make

CMakeFiles/test_snake.dir/test.cpp.o: CMakeFiles/test_snake.dir/flags.make
CMakeFiles/test_snake.dir/test.cpp.o: /home/zyf/Homework/GreedySnake/test.cpp
CMakeFiles/test_snake.dir/test.cpp.o: CMakeFiles/test_snake.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zyf/Homework/GreedySnake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_snake.dir/test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_snake.dir/test.cpp.o -MF CMakeFiles/test_snake.dir/test.cpp.o.d -o CMakeFiles/test_snake.dir/test.cpp.o -c /home/zyf/Homework/GreedySnake/test.cpp

CMakeFiles/test_snake.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_snake.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zyf/Homework/GreedySnake/test.cpp > CMakeFiles/test_snake.dir/test.cpp.i

CMakeFiles/test_snake.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_snake.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zyf/Homework/GreedySnake/test.cpp -o CMakeFiles/test_snake.dir/test.cpp.s

# Object files for target test_snake
test_snake_OBJECTS = \
"CMakeFiles/test_snake.dir/test.cpp.o"

# External object files for target test_snake
test_snake_EXTERNAL_OBJECTS =

test_snake: CMakeFiles/test_snake.dir/test.cpp.o
test_snake: CMakeFiles/test_snake.dir/build.make
test_snake: libGreedySnake.so
test_snake: /home/zyf/ct_icp-old_master/cmake-build-Release/external/yaml-cpp/src/yaml-cpp-build/libyaml-cpp.a
test_snake: CMakeFiles/test_snake.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zyf/Homework/GreedySnake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_snake"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_snake.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_snake.dir/build: test_snake
.PHONY : CMakeFiles/test_snake.dir/build

CMakeFiles/test_snake.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_snake.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_snake.dir/clean

CMakeFiles/test_snake.dir/depend:
	cd /home/zyf/Homework/GreedySnake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zyf/Homework/GreedySnake /home/zyf/Homework/GreedySnake /home/zyf/Homework/GreedySnake/build /home/zyf/Homework/GreedySnake/build /home/zyf/Homework/GreedySnake/build/CMakeFiles/test_snake.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_snake.dir/depend

