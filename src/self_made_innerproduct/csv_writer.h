#include <iostream>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <filesystem>
#include <iterator>
using namespace std;
namespace fs = std::filesystem;


/**
 * ### Outline ###
 * Input: uint32_t[]; a long integer array.
 * Aim: To write the array into a csv file in correct order for svm training.
 * 1. Need the row number and column number of each file for indexing.
 * 2. Use a 2D vector to document data
 * 3. Write the 2D vector into a .csv file.
 */


/**
 * To get row number of a .csv file.
 * @param: file_path: string; path of a file.
 * return: row_num: int; row number of the file.
 */
int get_file_row_num(string file_path);


/**
 * To get column number of a .csv file. All files in target directory have the same column number!
 * @param: file_path: string; path of a file.
 * return: col_num: int; column number of the file.
 */
int get_file_col_num(string file_path);


/**
 * To get row number of all .csv files in target directory.
 * @param: dir_path: string; path of target directory.
 * return: row_nums: vector<int>; row numbers of files in target directory.
 */
vector<int> get_all_file_row_num(string dir_path);


/**
 * Get length of all sections of dot product results in a vector(1 file vs. rest of the file).
 * @param: row_nums: vector<int>; vector containing row numbers of files in target directory.
 * return: vec_section: vector<int>; 
 */
vector<int> get_section_vec(vector<int> row_nums);


/**
 * Get length of subsection of dot product results in a vector(1 file vs. each of rest of the file).
 * @param: row_nums: vector<int>; vector containing row numbers of files in target directory.
 * return: vec_subsection: vector<int>
 */
vector<vector<int>> get_subsection_vec(vector<int> row_nums);


/**
 * Get the dot product matrix.
 * @param: sorted_res_vec: vector<vector<uint32_t>>; Sorted result vector.
 * return: dp_mat: vector<vector<uint32_t>>; dot product matrix, each cell is a result from any 2 vectors in order.
 */
vector<vector<uint32_t>> get_dp_matrix(vector<vector<uint32_t>> sorted_res_vec);


/**
 * Write the product matrix into csv file locally.
 * @param: input_mat: vector<vector<uint32_t>>; 2D vector containing ordered dot product matrix.
 */
void write_matrix_into_csv(vector<vector<uint32_t>> dp_mat);