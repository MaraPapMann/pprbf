#include <random>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

#ifndef GENERATE_RANDOM_DATA
#define GENERATE_RANDOM_DATA

class random_data_arrays
{
private:
    int array_length;
    int dim;
public:
    random_data_arrays(int arr_len, int dim):
    array_length(arr_len),
    dim(dim)
    {};

    uint16_t* get_random_data_array();

    uint16_t* array_a = get_random_data_array();

    uint16_t* array_b = get_random_data_array();
};

#endif