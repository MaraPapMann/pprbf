#include <vector>
using namespace std;
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <filesystem>
#include "../ABY/src/abycore/aby/abyparty.h"
namespace fs = std::filesystem;

// Aggregate the first vector
vector<uint32_t> aggregate_vector_1st(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b);

// Aggregate the second vector
vector<uint32_t> aggregate_vector_2nd(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b);

// Get all files' paths in directory as vector
vector<string> get_all_file_in_dir(string path, e_role role);

// Record the number of rows for next step#include 
/**
vector<int> getNumberOfRowsInFiles(vector<string> files){
		vector<int> vec;
		for(string file:files){
			CSVReader r(file);
			vec.push_back(r.getData().size());
		}
		return vec;
}
*/

// Only the dimension of vector matters in this context, do not really need to document the point of each segmentation

// Create the first long vector
vector<uint32_t> generate_1st_long_vector_for_all_files_in_dir(vector<string> file_vec);

// Create the second long vector
vector<uint32_t> generate_2nd_long_vector_for_all_files_in_dir(vector<string> file_vec);

// Get dimension of vector
int get_dimension_of_2dvector(vector<vector<uint32_t>> vec);