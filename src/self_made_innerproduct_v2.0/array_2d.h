#include <ENCRYPTO_utils/crypto/crypto.h>

class array_2d
{
private:
    uint32_t* array; 
    int nrow;
    int ncol;
public:
    array_2d(uint32_t* array, int nrow, int ncol):
    array(array),
    nrow(nrow),
    ncol(ncol)
    {}
};
