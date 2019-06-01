/**
 \title     ABY Probe
 \author    Huajie Chen
 \copyright ABY Development Team
 \brief     Realizing innerproduct circuit
*/

//Utility libs
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
#include "csv_parser.h"
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;


share* BuildInnerProductCircuit(share *s_x, share *s_y, uint32_t num, ArithmeticCircuit *ac, uint32_t dim) {

		// pairwise multiplication of all input values
		s_x = ac->PutMULGate(s_x, s_y);
		
		for (int i = 0; i < num/dim; i++)
		{
			int idx = i*dim;
			uint32_t posids[dim] = {idx, idx+1, idx+2};
			share* sub_s_x = ac->PutSubsetGate(s_x, posids, dim);  // Separate the SIMD according to dimension
			sub_s_x = ac->PutSplitterGate(sub_s_x);
			for (int j = 1; j < 10; j++)
			{
				sub_s_x->set_wire_id(0, ac->PutADDGate(sub_s_x->get_wire_id(0), sub_s_x->get_wire_id(j)));  // Summing up multiplication
			}
			sub_s_x->set_bitlength(1);  // Discarding wires except for the summation
			s_x->set_wire_id(i, sub_s_x->get_wire_id(0));  // Put the dot product to the right position of s_x
		}
		// split SIMD gate to separate wires (size many)
		//s_x = ac->PutSplitterGate(s_x);

		// add up the individual multiplication results and store result on wire 0
		// in arithmetic sharing ADD is for free, and does not add circuit depth, thus simple sequential adding
		/**
		for (i = 1; i < num; i++) {
				s_x->set_wire_id(0, ac->PutADDGate(s_x->get_wire_id(0), s_x->get_wire_id(i)));
		}
		*/

		// discard all wires, except the addition result
		s_x->set_bitlength(num/dim);	

		return s_x;
}

// For loop summation; Combination gate to tranpose; Subset gate to extract the needed values.

// Need input vector xvals & yvals
int32_t inner_product_circuit(e_role role, const std::string& address, uint32_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, vector<uint32_t> xvals, vector<uint32_t> yvals, uint32_t dim) {
    
    ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads,
			mt_alg);

    std::vector<Sharing*>& sharings = party->GetSharings();

    ArithmeticCircuit* circ =
			(ArithmeticCircuit*) sharings[sharing]->GetCircuitBuildRoutine();

    share *s_x_vec, *s_y_vec, *s_out;
    uint32_t num = xvals.size();
		cout << "Hi" << endl;
		cout<<num << ", " << dim << endl;
		cout << num / dim <<endl;
		cout << "check" << endl;

    s_x_vec = circ->PutSIMDINGate(num, xvals.data(), 32, SERVER);
	  s_y_vec = circ->PutSIMDINGate(num, yvals.data(), 32, CLIENT);


    s_out = BuildInnerProductCircuit(s_x_vec, s_y_vec, num,
			(ArithmeticCircuit*) circ, dim);

		

		s_out = circ -> PutOUTGate(s_out, ALL);

		party -> ExecCircuit();

		
		// Output an array
		uint32_t out_bitlen, out_nvals, *out_vals;
		s_out -> get_clear_value_vec(&out_vals, &out_bitlen, &out_nvals);

		uint32_t v_sum = 0;

		for (uint32_t i = 0; i < xvals.size(); i++)
		{
				uint32_t x = xvals[i];
				uint32_t y = yvals[i];
				v_sum += x*y;
		}
		
		std::cout << "\nCircuit Result: " << out_vals[0] << endl;

		/**
		for (int i=0; i<(sizeof(out_vals)/sizeof(*out_vals)); i++)
		{
			cout << out_vals[i] << ", ";
		}
		*/
		cout << endl;
		std::cout << "\nVerification Result: " << v_sum << std::endl;

		delete s_x_vec;
		delete s_y_vec;
		delete party;

		return 0;
        }
	
int32_t read_test_options(int32_t* argcp, char*** argvp, e_role* role,
		uint32_t* bitlen, uint32_t* nvals, uint32_t* secparam, std::string* address,
		uint32_t* port, int32_t* test_op, string* dir) {

		uint32_t int_role = 0, int_port = 0;

		parsing_ctx options[] =
				{ { (void*) &int_role, T_NUM, "r", "Role: 0/1", true, false },
					{ (void*) nvals, T_NUM, "n",	"Number of elements for inner product", false, false },
					{	(void*) bitlen, T_NUM, "b", "Bit-length, default 32", false, false },
					{ (void*) secparam, T_NUM, "s", "Symmetric Security Bits, default: 128", false, false },
					{	(void*) address, T_STR, "a", "IP-address, default: localhost", false, false },
					{	(void*) &int_port, T_NUM, "p", "Port, default: 7766", false, false },
					{ (void*) test_op, T_NUM, "t", "Single test (leave out for all operations), default: off",
						false, false }, 
					{	(void*) dir, T_STR, "d", "Directory containing .csv files", false, false }
					};

		if (!parse_options(argcp, argvp, options,
				sizeof(options) / sizeof(parsing_ctx))) {
			print_usage(*argvp[0], options, sizeof(options) / sizeof(parsing_ctx));
			std::cout << "Exiting" << std::endl;
			exit(0);
		}

		assert(int_role < 2);
		*role = (e_role) int_role;

		if (int_port != 0) {
			assert(int_port < 1 << (sizeof(uint32_t) * 8));
			*port = (uint32_t) int_port;
		}

		return 0;
}

/**
 * I: Two CSV file
 * TODO: Parse them as 2d vector: DONE
 * i row, j col in 1st .csv, k row, j col in 2nd .csv. (Same dimension in each row)
 * TODO: Generate 1st aggregated vector of length j*k*i: DONE
 * TODO: Generate 2nd aggregated vecotr of length j*k*i: DONE
 * TODO: Construct 2 long vector containing all files and informations needed for the innerproduct: DONE
 * TODO: Put two aggregated vector into SIMD Gate:
 * TODO: Get innerproduct of the SIMD Shares:
 * TODO: Transpose the SIMD Shares:
 * TODO: Split the SIMD Shares according to j:
 * TODO: Put Out Gate:
 */

// Aggregate the first vector
vector<uint32_t> aggregate_vector_1st(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
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
vector<uint32_t> aggregate_vector_2nd(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
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

// Get all files' paths in directory as vector
vector<string> get_all_file_in_dir(string path){
	vector<string> file_vec;
  for (const auto & entry : fs::directory_iterator(path))
	{
      file_vec.push_back(entry.path());
	}
	return file_vec;
}

// Record the number of rows for next step
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
vector<uint32_t> generate_1st_long_vector_for_all_files_in_dir(vector<string> file_vec){
		vector<uint32_t> vec_to_return;
		for (int i = 0; i < file_vec.size()-1; i++)
		{
			CSVReader x_csv(file_vec[i]);
			vector<vector<uint32_t>> vec_a = x_csv.getData();
			for (int j = i+1; j < file_vec.size(); j++)
			{
				CSVReader y_csv(file_vec[j]);
				vector<vector<uint32_t>> vec_b = y_csv.getData();
				vector<uint32_t> temp_vec = aggregate_vector_1st(vec_a, vec_b);
				vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
			}
		}
		return vec_to_return;
}

// Create the second long vector
vector<uint32_t> generate_2nd_long_vector_for_all_files_in_dir(vector<string> file_vec){
		vector<uint32_t> vec_to_return;
		for (int i = 0; i < file_vec.size()-1; i++)
		{
			CSVReader x_csv(file_vec[i]);
			vector<vector<uint32_t>> vec_a = x_csv.getData();
			for (int j = i+1; j < file_vec.size(); j++)
			{
				CSVReader y_csv(file_vec[j]);
				vector<vector<uint32_t>> vec_b = y_csv.getData();
				vector<uint32_t> temp_vec = aggregate_vector_2nd(vec_a, vec_b);
				vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
			}
		}
		return vec_to_return;
}

// Get dimension of vector
int get_dimension_of_2dvector(vector<vector<uint32_t>> vec){
	return vec[0].size();
}

/**
 * Get names of all files in one directory as list

int main(int argc, char** argv){
	CSVReader x_csv("../csv_files/x.csv"), y_csv("../csv_files/y.csv");
	vector<vector<uint32_t>> vec_a, vec_b;
	vec_a = x_csv.getData();
	vec_b = y_csv.getData();
	vector<uint32_t> vec_1st, vec_2nd;
	vec_1st = aggregate_vector_1st(vec_a, vec_b);
	vec_2nd = aggregate_vector_2nd(vec_a, vec_b);
	for(uint32_t out:vec_1st){
		cout << out;
	}
	cout << "" << endl;
	for(uint32_t out:vec_2nd){
		cout << out;
	}
}
*/

int main(int argc, char** argv) {

		e_role role;
		uint32_t bitlen = 16, nvals = 128, secparam = 128, nthreads = 1;
		uint32_t port = 7766;
		std::string address = "127.0.0.1";
		int32_t test_op = -1;
		e_mt_gen_alg mt_alg = MT_OT;
		string dir = "../csv_files/";

		read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op, &dir);

		seclvl seclvl = get_sec_lvl(secparam);

		vector<uint32_t> x_vec, y_vec;  // can use int[] array
		vector<string> file_vec = get_all_file_in_dir(dir);  // Get all file in a directory
		CSVReader csv(file_vec[0]);
		uint32_t dim = get_dimension_of_2dvector(csv.getData());
		x_vec = generate_1st_long_vector_for_all_files_in_dir(file_vec);
		y_vec = generate_2nd_long_vector_for_all_files_in_dir(file_vec);

		// call inner product routine. set size with cmd-parameter -n <size>
		inner_product_circuit(role, address, port, seclvl, 1, 32, nthreads, mt_alg, S_ARITH, x_vec, y_vec, dim);

		return 0;
}
