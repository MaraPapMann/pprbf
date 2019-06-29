cmake_minimum_required(VERSION 3.12)
project(ABY LANGUAGES CXX)


if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
    message(FATAL_ERROR "ABY requires at least g++-8")
endif()

find_package(ENCRYPTO_utils REQUIRED)
find_package(OTExtension REQUIRED)
find_package(GMP REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost 1.66.0 REQUIRED COMPONENTS thread system)
find_package(ABY QUIET)
if(ABY_FOUND)
	message(STATUS "Found ABY")
elseif (NOT ABY_FOUND AND NOT TARGET ABY::aby)
	message("ABY was not found: add ABY subdirectory")
 	add_subdirectory(extern/ABY)

endif()
add_executable(self_made_innerproduct self_made_innerproduct.cpp csv_parser.cpp generate_simulated_data.cpp vector_process.cpp csv_writer.cpp)
target_link_libraries(self_made_innerproduct ABY::aby ENCRYPTO_utils::encrypto_utils)
