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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kaznad/7colors

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaznad/7colors

# Include any dependencies generated for this target.
include CMakeFiles/7colors.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/7colors.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/7colors.dir/flags.make

CMakeFiles/7colors.dir/main.c.o: CMakeFiles/7colors.dir/flags.make
CMakeFiles/7colors.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaznad/7colors/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/7colors.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/7colors.dir/main.c.o   -c /home/kaznad/7colors/main.c

CMakeFiles/7colors.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/7colors.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kaznad/7colors/main.c > CMakeFiles/7colors.dir/main.c.i

CMakeFiles/7colors.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/7colors.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kaznad/7colors/main.c -o CMakeFiles/7colors.dir/main.c.s

CMakeFiles/7colors.dir/board.c.o: CMakeFiles/7colors.dir/flags.make
CMakeFiles/7colors.dir/board.c.o: board.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaznad/7colors/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/7colors.dir/board.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/7colors.dir/board.c.o   -c /home/kaznad/7colors/board.c

CMakeFiles/7colors.dir/board.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/7colors.dir/board.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kaznad/7colors/board.c > CMakeFiles/7colors.dir/board.c.i

CMakeFiles/7colors.dir/board.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/7colors.dir/board.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kaznad/7colors/board.c -o CMakeFiles/7colors.dir/board.c.s

# Object files for target 7colors
7colors_OBJECTS = \
"CMakeFiles/7colors.dir/main.c.o" \
"CMakeFiles/7colors.dir/board.c.o"

# External object files for target 7colors
7colors_EXTERNAL_OBJECTS =

7colors: CMakeFiles/7colors.dir/main.c.o
7colors: CMakeFiles/7colors.dir/board.c.o
7colors: CMakeFiles/7colors.dir/build.make
7colors: CMakeFiles/7colors.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kaznad/7colors/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable 7colors"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/7colors.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/7colors.dir/build: 7colors

.PHONY : CMakeFiles/7colors.dir/build

CMakeFiles/7colors.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/7colors.dir/cmake_clean.cmake
.PHONY : CMakeFiles/7colors.dir/clean

CMakeFiles/7colors.dir/depend:
	cd /home/kaznad/7colors && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kaznad/7colors /home/kaznad/7colors /home/kaznad/7colors /home/kaznad/7colors /home/kaznad/7colors/CMakeFiles/7colors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/7colors.dir/depend

