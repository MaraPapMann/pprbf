# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_SOURCE_DIR = /home/chen/Git_repositories/pprbf/src/self_made_innerproduct

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build

# Include any dependencies generated for this target.
include CMakeFiles/self_made_innerproduct.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/self_made_innerproduct.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/self_made_innerproduct.dir/flags.make

CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o: CMakeFiles/self_made_innerproduct.dir/flags.make
CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o: ../self_made_innerproduct.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o -c /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/self_made_innerproduct.cpp

CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/self_made_innerproduct.cpp > CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.i

CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/self_made_innerproduct.cpp -o CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.s

CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o: CMakeFiles/self_made_innerproduct.dir/flags.make
CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o: ../csv_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o -c /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/csv_parser.cpp

CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/csv_parser.cpp > CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.i

CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/csv_parser.cpp -o CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.s

# Object files for target self_made_innerproduct
self_made_innerproduct_OBJECTS = \
"CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o" \
"CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o"

# External object files for target self_made_innerproduct
self_made_innerproduct_EXTERNAL_OBJECTS =

self_made_innerproduct: CMakeFiles/self_made_innerproduct.dir/self_made_innerproduct.cpp.o
self_made_innerproduct: CMakeFiles/self_made_innerproduct.dir/csv_parser.cpp.o
self_made_innerproduct: CMakeFiles/self_made_innerproduct.dir/build.make
self_made_innerproduct: /usr/local/lib/libaby.a
self_made_innerproduct: /usr/local/lib/libencrypto_utils.a
self_made_innerproduct: /usr/local/lib/libotextension.a
self_made_innerproduct: /usr/local/lib/libencrypto_utils.a
self_made_innerproduct: /usr/local/lib/libmiracl.a
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libboost_thread.so
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libboost_system.so
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
self_made_innerproduct: /usr/local/lib/libgmpxx.so
self_made_innerproduct: /usr/lib/x86_64-linux-gnu/libcrypto.so
self_made_innerproduct: /usr/local/lib/libgmp.so
self_made_innerproduct: CMakeFiles/self_made_innerproduct.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable self_made_innerproduct"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/self_made_innerproduct.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/self_made_innerproduct.dir/build: self_made_innerproduct

.PHONY : CMakeFiles/self_made_innerproduct.dir/build

CMakeFiles/self_made_innerproduct.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/self_made_innerproduct.dir/cmake_clean.cmake
.PHONY : CMakeFiles/self_made_innerproduct.dir/clean

CMakeFiles/self_made_innerproduct.dir/depend:
	cd /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/Git_repositories/pprbf/src/self_made_innerproduct /home/chen/Git_repositories/pprbf/src/self_made_innerproduct /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build /home/chen/Git_repositories/pprbf/src/self_made_innerproduct/build/CMakeFiles/self_made_innerproduct.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/self_made_innerproduct.dir/depend

