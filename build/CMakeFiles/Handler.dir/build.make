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
CMAKE_SOURCE_DIR = /home/nick/progs/C/t/proj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nick/progs/C/t/proj/build

# Include any dependencies generated for this target.
include CMakeFiles/Handler.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Handler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Handler.dir/flags.make

CMakeFiles/Handler.dir/main.cpp.o: CMakeFiles/Handler.dir/flags.make
CMakeFiles/Handler.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nick/progs/C/t/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Handler.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Handler.dir/main.cpp.o -c /home/nick/progs/C/t/proj/main.cpp

CMakeFiles/Handler.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Handler.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nick/progs/C/t/proj/main.cpp > CMakeFiles/Handler.dir/main.cpp.i

CMakeFiles/Handler.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Handler.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nick/progs/C/t/proj/main.cpp -o CMakeFiles/Handler.dir/main.cpp.s

# Object files for target Handler
Handler_OBJECTS = \
"CMakeFiles/Handler.dir/main.cpp.o"

# External object files for target Handler
Handler_EXTERNAL_OBJECTS =

Handler: CMakeFiles/Handler.dir/main.cpp.o
Handler: CMakeFiles/Handler.dir/build.make
Handler: tmp/libmyHandler.a
Handler: CMakeFiles/Handler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nick/progs/C/t/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Handler"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Handler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Handler.dir/build: Handler

.PHONY : CMakeFiles/Handler.dir/build

CMakeFiles/Handler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Handler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Handler.dir/clean

CMakeFiles/Handler.dir/depend:
	cd /home/nick/progs/C/t/proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nick/progs/C/t/proj /home/nick/progs/C/t/proj /home/nick/progs/C/t/proj/build /home/nick/progs/C/t/proj/build /home/nick/progs/C/t/proj/build/CMakeFiles/Handler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Handler.dir/depend

