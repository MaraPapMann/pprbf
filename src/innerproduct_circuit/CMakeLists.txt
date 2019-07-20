add_executable(innerproduct.exe long_array.cpp csv_parser.cpp innerproduct_circuit.cpp read_test_options.cpp csv_writer.cpp)
target_link_libraries(innerproduct.exe ABY::aby ENCRYPTO_utils::encrypto_utils)
