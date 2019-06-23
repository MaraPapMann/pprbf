#include <vector>
using namespace std;
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <filesystem>
#include "../ABY/src/abycore/aby/abyparty.h"
namespace fs = std::filesystem;


/**
 * Generate the first long vector for multiplication in gate.
 * @param: input_3d_vec: vector<vector<vector<uint32_t>>>; a 3D vector containing needed data.
 * return: vec_to_return: vector<uint32_t>; a 1D vector long vector containing needed data.
 */
vector<uint32_t> aggregate_vector_1st(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b);


/**
 * Generate the second long vector for multiplication in gate.
 * @param: input_3d_vec: vector<vector<vector<uint32_t>>>; a 3D vector containing needed data.
 * return: vec_to_return: vector<uint32_t>; a 1D vector long vector containing needed data.
 */
vector<uint32_t> aggregate_vector_2nd(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b);


/**
 * Get paths of all files in directory as strings
 * @param: path: string; path to the directory.
 * @param: role: e_role; SERVER, CLIENT, ALL
 * return: file_vec: vector<string>; a 1D vector containing paths of all files in target directory.
 */
vector<string> get_all_file_in_dir(string path, e_role role);


/**
 * Generate the first long vector for all files in target directory
 * @param: file_vec: vector<string>; 
 * return: vec_to_return: vector<uint32_t>; first long vector for multiplication
 */
vector<uint32_t> generate_1st_long_vector_for_all_files_in_dir(vector<string> file_vec);


/**
 * Generate the second long vector for all files in target directory
 * @param: file_vec: vector<string>; 
 * return: vec_to_return: vector<uint32_t>; second long vector for multiplication
 */
vector<uint32_t> generate_2nd_long_vector_for_all_files_in_dir(vector<string> file_vec);


/**
 * Get dimension of vector(column number) in a 2D vector
 * @param: vec: vector<vector<uint32_t>>; a 2D vector
 * return: integer; the dimension of one single vector in 2D vector.
 */
int get_dimension_of_2dvector(vector<vector<uint32_t>> vec);