add_executable(self_dot_product.exe csv_parser.cpp self_dot_product.cpp read_test_options.cpp)
target_link_libraries(self_dot_product.exe ABY::aby ENCRYPTO_utils::encrypto_utils)
