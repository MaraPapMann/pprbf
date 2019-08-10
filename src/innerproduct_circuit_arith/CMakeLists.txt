add_executable(innerproduct_arith.exe long_array.cpp csv_parser.cpp innerproduct_circuit_arith.cpp read_test_options.cpp csv_writer.cpp self_dot_product_vector.cpp)
target_link_libraries(innerproduct_arith.exe ABY::aby ENCRYPTO_utils::encrypto_utils)
