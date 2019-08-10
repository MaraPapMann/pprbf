add_executable(innerproduct_bool.exe long_array.cpp csv_parser.cpp innerproduct_circuit_bool.cpp read_test_options.cpp csv_writer.cpp self_dot_product_vector.cpp)
target_link_libraries(innerproduct_bool.exe ABY::aby ENCRYPTO_utils::encrypto_utils)
