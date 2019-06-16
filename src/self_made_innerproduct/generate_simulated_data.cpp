#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

//ABY Party class
#include "../ABY/src/abycore/aby/abyparty.h"

// ABY Circuit and Sharing
#include "../ABY/src/abycore/circuit/booleancircuits.h"
#include "../ABY/src/abycore/circuit/arithmeticcircuits.h"
#include "../ABY/src/abycore/circuit/circuit.h"
#include "../ABY/src/abycore/sharing/sharing.h"

#include <math.h>
#include <cassert>
#include "iostream"
#include <boost/algorithm/string.hpp>
using namespace std;

#include <filesystem>
#include "./generate_simulated_data.h"
#include <vector>
using namespace std;

vector<vector<vector<uint32_t>>> generate_simulated_data(uint32_t dim, uint32_t num_hpt, int num_vecs[]){
    vector<vector<vector<uint32_t>>> vec_to_return;
    for(int k=0; k<num_hpt; k++){
        vector<vector<uint32_t>> temp_2d_vec;  // 2D vector to store random number vectors (one hospital)
        int len = num_vecs[k];
        for(int i=0; i<len; i++){
            vector<uint32_t> temp_1d_vec;  // 1D vector to store random number vectors (one vector)
            for(int j=0; j<dim; j++){
                uint32_t random_number = rand()%2;  // Generate random number
                temp_1d_vec.push_back(random_number);  // Take in random number
            }
            temp_2d_vec.push_back(temp_1d_vec);  // Take in 1D vector
        }
        vec_to_return.push_back(temp_2d_vec);  // Take in 2D vector
    }
    return vec_to_return;
}

// Aggregate the first vector
vector<uint32_t> aggregate_vector_1st_2(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
		int i = vec_a.size();
		int j = vec_a[0].size();
		int k = vec_b.size();
		vector<uint32_t> vec_1st;
		for (vector<uint32_t> vec:vec_a)
		{
			for (int l = 0; l < k; l++)
			{
				vec_1st.insert(vec_1st.end(), vec.begin(), vec.end());
			}
		}
		return vec_1st;
}

// Aggregate the second vector
vector<uint32_t> aggregate_vector_2nd_2(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
		int i = vec_a.size();
		int j = vec_a[0].size();
		int k = vec_b.size();
		vector<uint32_t> vec_2nd;
		for (int l = 0; l < i; l++)
		{
			for (vector<uint32_t> vec:vec_b)
			{
				vec_2nd.insert(vec_2nd.end(), vec.begin(), vec.end());
			}
		}
		return vec_2nd;
}

vector<uint32_t> generate_1st_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec){
    vector<uint32_t> vec_to_return;
    for(int i=0; i<input_3d_vec.size()-1; i++){
        vector<vector<uint32_t>> cur_2d_vec_a = input_3d_vec[i];
        for(int j=i+1; j<input_3d_vec.size(); j++){
            vector<vector<uint32_t>> cur_2d_vec_b = input_3d_vec[j];
            vector<uint32_t> temp_vec = aggregate_vector_1st_2(cur_2d_vec_a, cur_2d_vec_b);
            vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
        }
    }
    return vec_to_return;
}

vector<uint32_t> generate_2nd_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec){
    vector<uint32_t> vec_to_return;
    for(int i=0; i<input_3d_vec.size()-1; i++){
        vector<vector<uint32_t>> cur_2d_vec_a = input_3d_vec[i];
        for(int j=i+1; j<input_3d_vec.size(); j++){
            vector<vector<uint32_t>> cur_2d_vec_b = input_3d_vec[j];
            vector<uint32_t> temp_vec = aggregate_vector_2nd_2(cur_2d_vec_a, cur_2d_vec_b);
            vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
        }
    }
    return vec_to_return;
}

void test_generate_simulated_data(vector<vector<vector<uint32_t>>> probe_vec){
    for(vector<vector<uint32_t>> cur_2d_vec:probe_vec){
        cout<<"Hospital X"<<endl;
        for(vector<uint32_t> cur_1d_vec:cur_2d_vec){
            cout<<"Vector X"<<endl;
            for(uint32_t cur_num:cur_1d_vec){
                cout<<cur_num<<", ";  // Print a number
            }
            cout<<endl;  // Print a vector
        }
        cout<<endl;
    }
}

void test_generate_long_vec(vector<uint32_t> long_vec_a, vector<uint32_t> long_vec_b){
    cout<<"Long vector a"<<endl;
    for(uint32_t a:long_vec_a){
        cout<<a<<", ";
    }
    cout<<"Long vector b"<<endl;
    for(uint32_t b:long_vec_b){
        cout<<b<<", ";
    }
}

/**
int main(){
    uint32_t dim = 300;
    uint32_t num_hpt = 3;
    int num_vec[num_hpt] = {3, 4, 5};
    vector<vector<vector<uint32_t>>> probe_vec = generate_simulated_data(dim, num_hpt, num_vec);
    vector<uint32_t> long_vec_a = generate_1st_long_vec(probe_vec);
    vector<uint32_t> long_vec_b = generate_2nd_long_vec(probe_vec);

    test_generate_long_vec(long_vec_a, long_vec_b);

    return 0;
}
*/