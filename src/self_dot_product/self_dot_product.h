/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      1.	Parse original csv files in given directory;
 *      2.  Calculate dot product;
 *      3.  Write dot product into csv files.
 *  @Input:
 *      1.  path: path to the target directory;
 *  @Output:
 *      1. csv files containing dot-products.
 */


#include <vector>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include "csv_parser.h"
#include <sys/types.h>
#include <dirent.h>
#include <iterator>
#include <random>
using namespace std;


class self_dot_product
{
private:
    string path;  // Path to the target directory.

    // Get all files' paths in given directory into a vector.
    vector<string> get_all_file_in_dir();

    // A vector containing paths to files.
    vector<string> file_vector = self_dot_product::get_all_file_in_dir();

    // Parse file as vector.
    vector<vector<uint16_t>> parse_file_as_vec(string file_path);

    // Calculate the self dot products.
    vector<uint16_t> calc_self_dp(vector<vector<uint16_t>> parsed_file);

    // Get all self dot products in a 2D vector.
    vector<vector<uint16_t>> get_self_dp_all();

    vector<vector<uint16_t>> self_dp = self_dot_product::get_self_dp_all();  // A 2D vector containing self dot products.

    // Split dot products into 2 parts
    vector<vector<uint16_t>> split_dp_into_2();

    vector<vector<uint16_t>> split_dp = self_dot_product::split_dp_into_2();  // A 2D vector containing split self dot products.

public:
    self_dot_product(string path):
    path(path)
    {};
    
    // Write the results into csv files.
    void output_csv_files(string out_file);
};
