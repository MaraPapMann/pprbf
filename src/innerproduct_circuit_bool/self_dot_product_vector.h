/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      1.	Parse all self dot product csv files in given directory and create 1 long vector;
 *      2.  Document the needed information of the long vector.
 *  @Input:
 *      1.  path: path to the target directory;
 * 		2.	role: SERVER / CLIENT;
 *  @Output:
 *      1.	dim: dimension of a vector(column number of a file);
 * 		2.	self_dot_product_vector_len: length of a long array;
 * 		3.	self_dot_product_vector_a: long array a;
 *      4.  self_dot_product_vector_b: long array b;
 *      5.  row_nums: Vector containing row numbers;
 *      6.  res_array_length: result array length.
 */
#ifndef SELF_DOT_PRODUCT_VECTOR_
#define SELF_DOT_PRODUCT_VECTOR_

#include <vector>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include "../ABY/src/abycore/aby/abyparty.h"
#include "csv_parser.h"
#include <sys/types.h>
#include <dirent.h>
#include <iterator>

class self_dot_product_vector
{
private:
    string path; // Path to the target directoty.
    e_role role; // Role: SERVER or CLIENT.

    // Get all files' paths in given directory into a vector.
    vector<string> get_all_file_in_dir();

    // A vector containing paths to files.
    vector<string> file_vector = self_dot_product_vector::get_all_file_in_dir();

    // Get dimension of one single vector in all files (column number).
    vector<int> get_dim_vec();

    // Get long vector.
    vector<uint16_t> get_long_vec();

    // Get the length of long array.
    int get_self_dp_vec_len();

public:
    // Initiator.
    self_dot_product_vector(string path, e_role role):
        path(path),
        role(role)
        {};

    // Dimension(column number).
    vector<int> dim_vec = self_dot_product_vector::get_dim_vec();

    // Length of the long array.
    int self_dp_vec_len = self_dot_product_vector::get_self_dp_vec_len();

    // Long array a.
    vector<uint16_t> self_dp_vec = self_dot_product_vector::get_long_vec();

};

#endif