/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      1.	Parse all csv files in given directory and create 2 long arrays;
 *      2.  Document the needed information of the long arrays.
 *  @Input:
 *      1.  path: path to the target directory;
 * 		2.	role: SERVER / CLIENT;
 *  @Output:
 *      1.	dim: dimension of a vector(column number of a file);
 * 		2.	long_array_len: length of a long array;
 * 		3.	long_array_a: long array a;
 *      4.  long_array_b: long array b;
 *      5.  row_nums: Vector containing row numbers;
 *      6.  res_array_length: result array length.
 */

#include <vector>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include "../ABY/src/abycore/aby/abyparty.h"
#include "csv_parser.h"
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <iterator>
using namespace std;

class long_array
{
private:
    string path; // Path to the target directoty.
    e_role role; // Role: SERVER or CLIENT.
    
    // Get row numbers of all files into a vector.
    vector<int> get_row_nums_vec();

    // Get all files' paths in given directory into a vector.
    vector<string> get_all_file_in_dir();

    // A vector containing paths to files.
    vector<string> file_vector = long_array::get_all_file_in_dir();

    // Get dimension of one single vector in a file(column number).
    int get_dim();

    // Get one segmentation length of the long array generated from two files.
    int get_one_seg_len(string file_a, string file_b);
    
    // Get the length of long array.
    int get_long_array_len();

    // Get long array a.
    uint16_t* get_long_arr_a();

    // Get long array b.
    uint16_t* get_long_arr_b();

    // Get segmentations' length vector.
    vector<int> get_seg_len_vec();

public:
    // Initiator.
    long_array(string path, e_role role):
        path(path),
        role(role)
        {};

    // Dimension(column number).
    int dim = long_array::get_dim();
    
    // Length of the long array.
    int long_array_len = long_array::get_long_array_len();
    
    // Long array a.
    uint16_t* long_array_a = long_array::get_long_arr_a();

    // Long array b.
    uint16_t* long_array_b = long_array::get_long_arr_b();
    
    // Vector containing row numbers.
    vector<int> row_nums = long_array::get_row_nums_vec();

    // Result array length.
    int res_array_length = long_array_len / dim;

    // Segmentations' length vector.
    vector<int> seg_len_vec = long_array::get_seg_len_vec();
};

