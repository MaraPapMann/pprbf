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
CMAKE_SOURCE_DIR = /home/chen/Git_repositories/pprbf/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chen/Git_repositories/pprbf/src/build

# Include any dependencies generated for this target.
include benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/depend.make

# Include the progress variables for this target.
include benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/flags.make

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/flags.make
benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o: ../benchmark_bool_innerproduct/innerproduct_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o -c /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/innerproduct_test.cpp

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.i"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/innerproduct_test.cpp > CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.i

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.s"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/innerproduct_test.cpp -o CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.s

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/flags.make
benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o: ../benchmark_bool_innerproduct/common/innerproduct.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o -c /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/common/innerproduct.cpp

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.i"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/common/innerproduct.cpp > CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.i

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.s"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct/common/innerproduct.cpp -o CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.s

# Object files for target bool_innerproduct.exe
bool_innerproduct_exe_OBJECTS = \
"CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o" \
"CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o"

# External object files for target bool_innerproduct.exe
bool_innerproduct_exe_EXTERNAL_OBJECTS =

bin/bool_innerproduct.exe: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/innerproduct_test.cpp.o
bin/bool_innerproduct.exe: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/common/innerproduct.cpp.o
bin/bool_innerproduct.exe: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/build.make
bin/bool_innerproduct.exe: lib/libaby.a
bin/bool_innerproduct.exe: /usr/local/lib/libencrypto_utils.a
bin/bool_innerproduct.exe: /usr/local/lib/libotextension.a
bin/bool_innerproduct.exe: /usr/local/lib/libencrypto_utils.a
bin/bool_innerproduct.exe: /usr/local/lib/libmiracl.a
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_thread.so
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_system.so
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
bin/bool_innerproduct.exe: /usr/local/lib/libgmpxx.so
bin/bool_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libcrypto.so
bin/bool_innerproduct.exe: /usr/local/lib/libgmp.so
bin/bool_innerproduct.exe: benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/bool_innerproduct.exe"
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bool_innerproduct.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/build: bin/bool_innerproduct.exe

.PHONY : benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/build

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/clean:
	cd /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct && $(CMAKE_COMMAND) -P CMakeFiles/bool_innerproduct.exe.dir/cmake_clean.cmake
.PHONY : benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/clean

benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/depend:
	cd /home/chen/Git_repositories/pprbf/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/Git_repositories/pprbf/src /home/chen/Git_repositories/pprbf/src/benchmark_bool_innerproduct /home/chen/Git_repositories/pprbf/src/build /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct /home/chen/Git_repositories/pprbf/src/build/benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : benchmark_bool_innerproduct/CMakeFiles/bool_innerproduct.exe.dir/depend

