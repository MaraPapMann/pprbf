#include <vector>
#include <math.h>
using namespace std;


/**
 * Generate random 3D vector as simulated data.
 * @param: dim: uint32_t; dimension of a single vector(column number).
 * @param: num_hpt: uint32_t; number of hospital(file number).
 * @param: num_vecs: int; number of vectors in a list(row number).
 * return: vector_to_return: vector<vector<vector<uint32_t>>>; a 3D vector containing random generated simulated data.
 */
vector<vector<vector<uint32_t>>> generate_simulated_data(uint32_t dim, uint32_t num_hpt, int num_vecs[]);


/**
 * Generate the first long vector for multiplication in gate.
 * @param: input_3d_vec: vector<vector<vector<uint32_t>>>; a 3D vector containing needed data.
 * return: vec_to_return: vector<uint32_t>; a 1D vector long vector containing needed data.
 */
vector<uint32_t> generate_1st_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec);


/**
 * Generate the second long vector for multiplication in gate.
 * @param: input_3d_vec: vector<vector<vector<uint32_t>>>; a 3D vector containing needed data.
 * return: vec_to_return: vector<uint32_t>; a 1D vector long vector containing needed data.
 */
vector<uint32_t> generate_2nd_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec);