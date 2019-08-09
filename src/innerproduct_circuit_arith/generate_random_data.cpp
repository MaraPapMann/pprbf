#include "generate_random_data.h"


uint16_t* random_data_arrays::get_random_data_array(){
    uint16_t* arr = new uint16_t[array_length];
    for(int i=0; i<array_length; i++){
        arr[i] = rand() % 256;
    }
    return arr;
}