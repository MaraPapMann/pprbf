#include <vector>
#include <math.h>
using namespace std;

// Generate random 3D vector as simulated data.
vector<vector<vector<u_int32_t>>> generate_simulated_data(u_int32_t dim, u_int32_t num_hpt, int num_vecs[]);

// Generate the first long vector.
vector<uint32_t> generate_1st_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec);

// Generate the second long vector.
vector<uint32_t> generate_2nd_long_vec(vector<vector<vector<uint32_t>>> input_3d_vec);