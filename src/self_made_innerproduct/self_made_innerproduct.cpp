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
#include "../ABY/src/abycore/ABY_utils/ABYconstants.h"
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

#include "generate_simulated_data.h"
#include "vector_process.h"
#include <vector>
#include <filesystem>
namespace fs = std::filesystem;


share* BuildInnerProductCircuit(share *s_x, share *s_y, uint32_t num, ArithmeticCircuit *ac, uint32_t dim) {
	// pairwise multiplication of all input values
	s_x = ac->PutMULGate(s_x, s_y); // Now each nval is a value, need to be transposed so that each wire stands for one value.
	s_x = ac->PutSplitterGate(s_x); // Transposed.

	for(uint32_t i=0; i< num/dim; i++)
	{
		uint32_t idx = i*dim;
		for(uint32_t j=1; j<dim; j++)
		{
			s_x->set_wire_id(idx, ac->PutADDGate(s_x->get_wire_id(idx), s_x->get_wire_id(idx+j))); // Put the summation result into the right pos
		}
	}

	for(uint32_t i=0; i<num/dim; i++)
	{
		s_x->set_wire_id(i, s_x->get_wire_id(i*dim));
	}

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

    s_x_vec = circ->PutSharedSIMDINGate(num, xvals.data(), bitlen);
	s_y_vec = circ->PutSharedSIMDINGate(num, yvals.data(), bitlen);		

    s_out = BuildInnerProductCircuit(s_x_vec, s_y_vec, num,
			(ArithmeticCircuit*) circ, dim);

	s_out = circ -> PutOUTGate(s_out, ALL);

	party -> ExecCircuit();

	// Output an array
	uint32_t out_bitlen, out_nvals, *out_vals;
	s_out -> get_clear_value_vec(&out_vals, &out_bitlen, &out_nvals);

	uint32_t v_res[num/dim];

	for (uint32_t i = 0; i < num/dim; i++)
	{
		int idx = i*dim;
		int temp_sum = 0;
		for(int j=0; j<dim; j++)
		{
			temp_sum = temp_sum + (xvals[idx+j] * yvals[idx+j]);
		}
		v_res[i] = temp_sum;
	}
	
	std::cout << "\nCircuit Result: " << endl;
	for(int i=0; i<num/dim; i++)
	{
		if (i==sizeof(out_vals)-1)
		{
			cout<<out_vals[i]<<endl;
		}else
		{
			cout<<out_vals[i]<<", ";
		}
	}

	/**
	for (int i=0; i<(sizeof(out_vals)/sizeof(*out_vals)); i++)
	{
		cout << out_vals[i] << ", ";
	}
	*/
	cout << endl;
	std::cout << "\nVerification Result: " << std::endl;
	for(int i=0; i<num/dim; i++)
	{
		if (i==num/dim-1)
		{
			cout<<v_res[i]<<endl;
		}else
		{
			cout<<v_res[i]<<", ";
		}
	}

	delete s_x_vec;
	delete s_y_vec;
	delete party;

	return 0;
}

int32_t read_test_options(int32_t* argcp, char*** argvp, e_role* role,
	uint32_t* bitlen, uint32_t* nvals, uint32_t* secparam, std::string* address,
	uint32_t* port, int32_t* test_op, string* dir) 
	{
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
	uint32_t bitlen = 8, nvals = 128, secparam = 128, nthreads = 1;
	uint32_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
	
	string dir = "../../splitFile/csv_dir/";

	read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op, &dir);

	seclvl seclvl = get_sec_lvl(secparam);

	vector<uint32_t> x_vec, y_vec;  // can use int[] array
	// Read csv file part
	vector<string> file_vec = get_all_file_in_dir(dir, role);  // Get all file in a directory by role
	CSVReader csv(file_vec[0]);
	uint32_t dim = get_dimension_of_2dvector(csv.getData());
	x_vec = generate_1st_long_vector_for_all_files_in_dir(file_vec);
	y_vec = generate_2nd_long_vector_for_all_files_in_dir(file_vec);


	/**
	uint32_t dim = 150;
	uint32_t num_hpt = 20;
	int num_vec[num_hpt] = {7, 5, 3, 6, 2, 8, 3, 6, 3, 8, 9, 3, 1, 7, 3, 8, 4, 7, 9, 4};
	vector<vector<vector<uint32_t>>> simulated_data = generate_simulated_data(dim, num_hpt, num_vec);
	x_vec = generate_1st_long_vec(simulated_data);
	y_vec = generate_2nd_long_vec(simulated_data);
	cout<<"Size of the long vector"<<x_vec.size()<<endl;
	*/

	// call inner product routine. set size with cmd-parameter -n <size>
	inner_product_circuit(role, address, port, seclvl, 1, bitlen, nthreads, mt_alg, S_ARITH, x_vec, y_vec, dim);

	return 0;
}
