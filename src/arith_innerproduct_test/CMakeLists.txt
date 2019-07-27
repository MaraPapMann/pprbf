add_executable(arith_innerproduct.exe innerproduct_test.cpp common/innerproduct.cpp)
target_link_libraries(arith_innerproduct.exe ABY::aby ENCRYPTO_utils::encrypto_utils)
