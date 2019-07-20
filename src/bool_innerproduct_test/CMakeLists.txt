add_executable(bool_innerproduct.exe innerproduct_test.cpp common/innerproduct.cpp)
target_link_libraries(bool_innerproduct.exe ABY::aby ENCRYPTO_utils::encrypto_utils)