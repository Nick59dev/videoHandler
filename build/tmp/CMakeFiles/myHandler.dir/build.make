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
include tmp/CMakeFiles/myHandler.dir/depend.make

# Include the progress variables for this target.
include tmp/CMakeFiles/myHandler.dir/progress.make

# Include the compile flags for this target's objects.
include tmp/CMakeFiles/myHandler.dir/flags.make

tmp/CMakeFiles/myHandler.dir/processingFile.cpp.o: tmp/CMakeFiles/myHandler.dir/flags.make
tmp/CMakeFiles/myHandler.dir/processingFile.cpp.o: ../tmp/processingFile.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nick/progs/C/t/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tmp/CMakeFiles/myHandler.dir/processingFile.cpp.o"
	cd /home/nick/progs/C/t/proj/build/tmp && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/myHandler.dir/processingFile.cpp.o -c /home/nick/progs/C/t/proj/tmp/processingFile.cpp

tmp/CMakeFiles/myHandler.dir/processingFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myHandler.dir/processingFile.cpp.i"
	cd /home/nick/progs/C/t/proj/build/tmp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nick/progs/C/t/proj/tmp/processingFile.cpp > CMakeFiles/myHandler.dir/processingFile.cpp.i

tmp/CMakeFiles/myHandler.dir/processingFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myHandler.dir/processingFile.cpp.s"
	cd /home/nick/progs/C/t/proj/build/tmp && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nick/progs/C/t/proj/tmp/processingFile.cpp -o CMakeFiles/myHandler.dir/processingFile.cpp.s

# Object files for target myHandler
myHandler_OBJECTS = \
"CMakeFiles/myHandler.dir/processingFile.cpp.o"

# External object files for target myHandler
myHandler_EXTERNAL_OBJECTS =

tmp/libmyHandler.a: tmp/CMakeFiles/myHandler.dir/processingFile.cpp.o
tmp/libmyHandler.a: tmp/CMakeFiles/myHandler.dir/build.make
tmp/libmyHandler.a: tmp/CMakeFiles/myHandler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nick/progs/C/t/proj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmyHandler.a"
	cd /home/nick/progs/C/t/proj/build/tmp && $(CMAKE_COMMAND) -P CMakeFiles/myHandler.dir/cmake_clean_target.cmake
	cd /home/nick/progs/C/t/proj/build/tmp && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myHandler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tmp/CMakeFiles/myHandler.dir/build: tmp/libmyHandler.a

.PHONY : tmp/CMakeFiles/myHandler.dir/build

tmp/CMakeFiles/myHandler.dir/clean:
	cd /home/nick/progs/C/t/proj/build/tmp && $(CMAKE_COMMAND) -P CMakeFiles/myHandler.dir/cmake_clean.cmake
.PHONY : tmp/CMakeFiles/myHandler.dir/clean

tmp/CMakeFiles/myHandler.dir/depend:
	cd /home/nick/progs/C/t/proj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nick/progs/C/t/proj /home/nick/progs/C/t/proj/tmp /home/nick/progs/C/t/proj/build /home/nick/progs/C/t/proj/build/tmp /home/nick/progs/C/t/proj/build/tmp/CMakeFiles/myHandler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tmp/CMakeFiles/myHandler.dir/depend

