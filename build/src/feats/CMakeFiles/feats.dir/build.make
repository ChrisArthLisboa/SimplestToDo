# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lisboa/Documents/learning/SimplestToDo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lisboa/Documents/learning/SimplestToDo/build

# Include any dependencies generated for this target.
include src/feats/CMakeFiles/feats.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/feats/CMakeFiles/feats.dir/compiler_depend.make

# Include the progress variables for this target.
include src/feats/CMakeFiles/feats.dir/progress.make

# Include the compile flags for this target's objects.
include src/feats/CMakeFiles/feats.dir/flags.make

src/feats/CMakeFiles/feats.dir/main.c.o: src/feats/CMakeFiles/feats.dir/flags.make
src/feats/CMakeFiles/feats.dir/main.c.o: ../src/feats/main.c
src/feats/CMakeFiles/feats.dir/main.c.o: src/feats/CMakeFiles/feats.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lisboa/Documents/learning/SimplestToDo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/feats/CMakeFiles/feats.dir/main.c.o"
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT src/feats/CMakeFiles/feats.dir/main.c.o -MF CMakeFiles/feats.dir/main.c.o.d -o CMakeFiles/feats.dir/main.c.o -c /home/lisboa/Documents/learning/SimplestToDo/src/feats/main.c

src/feats/CMakeFiles/feats.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/feats.dir/main.c.i"
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lisboa/Documents/learning/SimplestToDo/src/feats/main.c > CMakeFiles/feats.dir/main.c.i

src/feats/CMakeFiles/feats.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/feats.dir/main.c.s"
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lisboa/Documents/learning/SimplestToDo/src/feats/main.c -o CMakeFiles/feats.dir/main.c.s

# Object files for target feats
feats_OBJECTS = \
"CMakeFiles/feats.dir/main.c.o"

# External object files for target feats
feats_EXTERNAL_OBJECTS =

src/feats/libfeats.a: src/feats/CMakeFiles/feats.dir/main.c.o
src/feats/libfeats.a: src/feats/CMakeFiles/feats.dir/build.make
src/feats/libfeats.a: src/feats/CMakeFiles/feats.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lisboa/Documents/learning/SimplestToDo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libfeats.a"
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && $(CMAKE_COMMAND) -P CMakeFiles/feats.dir/cmake_clean_target.cmake
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/feats.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/feats/CMakeFiles/feats.dir/build: src/feats/libfeats.a
.PHONY : src/feats/CMakeFiles/feats.dir/build

src/feats/CMakeFiles/feats.dir/clean:
	cd /home/lisboa/Documents/learning/SimplestToDo/build/src/feats && $(CMAKE_COMMAND) -P CMakeFiles/feats.dir/cmake_clean.cmake
.PHONY : src/feats/CMakeFiles/feats.dir/clean

src/feats/CMakeFiles/feats.dir/depend:
	cd /home/lisboa/Documents/learning/SimplestToDo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lisboa/Documents/learning/SimplestToDo /home/lisboa/Documents/learning/SimplestToDo/src/feats /home/lisboa/Documents/learning/SimplestToDo/build /home/lisboa/Documents/learning/SimplestToDo/build/src/feats /home/lisboa/Documents/learning/SimplestToDo/build/src/feats/CMakeFiles/feats.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/feats/CMakeFiles/feats.dir/depend
