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
include arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/depend.make

# Include the progress variables for this target.
include arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/progress.make

# Include the compile flags for this target's objects.
include arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/flags.make

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/flags.make
arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o: ../arith_innerproduct_test/innerproduct_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o -c /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/innerproduct_test.cpp

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.i"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/innerproduct_test.cpp > CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.i

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.s"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/innerproduct_test.cpp -o CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.s

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/flags.make
arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o: ../arith_innerproduct_test/common/innerproduct.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o -c /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/common/innerproduct.cpp

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.i"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/common/innerproduct.cpp > CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.i

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.s"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test/common/innerproduct.cpp -o CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.s

# Object files for target arith_innerproduct.exe
arith_innerproduct_exe_OBJECTS = \
"CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o" \
"CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o"

# External object files for target arith_innerproduct.exe
arith_innerproduct_exe_EXTERNAL_OBJECTS =

bin/arith_innerproduct.exe: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/innerproduct_test.cpp.o
bin/arith_innerproduct.exe: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/common/innerproduct.cpp.o
bin/arith_innerproduct.exe: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/build.make
bin/arith_innerproduct.exe: lib/libaby.a
bin/arith_innerproduct.exe: /usr/local/lib/libencrypto_utils.a
bin/arith_innerproduct.exe: /usr/local/lib/libotextension.a
bin/arith_innerproduct.exe: /usr/local/lib/libencrypto_utils.a
bin/arith_innerproduct.exe: /usr/local/lib/libmiracl.a
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_thread.so
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_system.so
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
bin/arith_innerproduct.exe: /usr/local/lib/libgmpxx.so
bin/arith_innerproduct.exe: /usr/lib/x86_64-linux-gnu/libcrypto.so
bin/arith_innerproduct.exe: /usr/local/lib/libgmp.so
bin/arith_innerproduct.exe: arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chen/Git_repositories/pprbf/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../bin/arith_innerproduct.exe"
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arith_innerproduct.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/build: bin/arith_innerproduct.exe

.PHONY : arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/build

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/clean:
	cd /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test && $(CMAKE_COMMAND) -P CMakeFiles/arith_innerproduct.exe.dir/cmake_clean.cmake
.PHONY : arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/clean

arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/depend:
	cd /home/chen/Git_repositories/pprbf/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chen/Git_repositories/pprbf/src /home/chen/Git_repositories/pprbf/src/arith_innerproduct_test /home/chen/Git_repositories/pprbf/src/build /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test /home/chen/Git_repositories/pprbf/src/build/arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : arith_innerproduct_test/CMakeFiles/arith_innerproduct.exe.dir/depend

