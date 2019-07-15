/**
 @title     Innerproduct Circuit
 @author    Huajie Chen
*/

//Utility libraries.
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

// ABY Party class.
#include "../ABY/src/abycore/aby/abyparty.h"

// ABY Circuit and Sharing.
#include "../ABY/src/abycore/ABY_utils/ABYconstants.h"
#include "../ABY/src/abycore/circuit/booleancircuits.h"
#include "../ABY/src/abycore/circuit/arithmeticcircuits.h"
#include "../ABY/src/abycore/circuit/circuit.h"
#include "../ABY/src/abycore/sharing/sharing.h"

// Basic packages.
#include <math.h>
#include <cassert>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>

// Self-produced codes.
#include "read_test_options.h"
#include "long_array.h"
#include "csv_writer.h"

using namespace std;

share* inner_product_circuit(share *s_x, share *s_y, int num, ArithmeticCircuit *ac, uint16_t dim) {
	// pairwise multiplication of all input values
	s_x = ac->PutMULGate(s_x, s_y); // Now each nval is a value, need to be transposed so that each wire stands for one value.
	s_x = ac->PutSplitterGate(s_x); // Transposed.

	// Summing up products for each dot product.
	for(int i=0; i< num/dim; i++)
	{
		int idx = i*dim;
		for(int j=1; j<dim; j++)
		{
			s_x->set_wire_id(idx, ac->PutADDGate(s_x->get_wire_id(idx), s_x->get_wire_id(idx+j))); // Put the summation result into the right pos
		}
	}

	// Setting dot products into the front of the share.
	for(int i=0; i<num/dim; i++)
	{
		s_x->set_wire_id(i, s_x->get_wire_id(i*dim));
	}

	// Discard all unnecessary wires except for the dot products.
	s_x->set_bitlength(num/dim);

	return s_x;
	delete s_x, s_y, ac;
}

// For loop summation; Combination gate to tranpose; Subset gate to extract the needed values.

// Need input vector xvals & yvals
uint32_t* general_circuit(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
		uint16_t nvals, uint16_t bitlen, uint16_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, long_array* two_long_arrays, int seg_len_limit) {
	
	// Array carrying the results.
	uint32_t* res_arr = new uint32_t[two_long_arrays->res_array_length];
	// Length of one segmentation.
	int seg_len = (two_long_arrays->long_array_len % seg_len_limit / two_long_arrays->dim) * two_long_arrays->dim;
	// Number of segmentations.
	int seg_num = two_long_arrays->long_array_len / seg_len;
	// Mod number for getting the final results.
	int mod_num = pow(2, bitlen);
	
	// Start point of one segmentation in long array.
	int sp = 0;
	// Start point of one segmentation in the result array.
	int res_sp = 0;
	for(int i=0; i<seg_num; i++){
		// Initiation of the ABY party.
		ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);
		// Get sharings.
		vector<Sharing*>& sharings = party->GetSharings();
		// Build the corresponding circuit according to the sharing type.
		ArithmeticCircuit* circ = (ArithmeticCircuit*) sharings[sharing]->GetCircuitBuildRoutine();
		
		// Long array a in segmentation.
		uint16_t* long_arr_a_in_seg;
		// Long array b in segmentation.
		uint16_t* long_arr_b_in_seg;
		// Sharings.
		share *s_x_vec, *s_y_vec, *s_out;

		// Segment the long array into segmentations.
		if (i != seg_num - 1)  // Not the very last one segmentation.
		{
			long_arr_a_in_seg = new uint16_t[seg_len];
			long_arr_b_in_seg = new uint16_t[seg_len];
			for(int i=0; i<seg_len; i++){
				long_arr_a_in_seg[i] = two_long_arrays->long_array_a[sp + i];
				long_arr_b_in_seg[i] = two_long_arrays->long_array_b[sp + i];
			}
			sp = sp + seg_len;

			// Put shared data as SIMD share in gate.
			s_x_vec = circ->PutSharedSIMDINGate(seg_len, long_arr_a_in_seg, bitlen);
			s_y_vec = circ->PutSharedSIMDINGate(seg_len, long_arr_b_in_seg, bitlen);

			// Call the inner product circuit function.
			s_out = inner_product_circuit(s_x_vec, s_y_vec, seg_len, circ, two_long_arrays->dim);
		}
		else
		{
			int last_seg_len = two_long_arrays->long_array_len - (seg_num - 1) * seg_len;
			long_arr_a_in_seg = new uint16_t[last_seg_len];
			long_arr_b_in_seg = new uint16_t[last_seg_len];
			for(int i=0; i<last_seg_len; i++){
				long_arr_a_in_seg[i] = two_long_arrays->long_array_a[sp + i];
				long_arr_b_in_seg[i] = two_long_arrays->long_array_b[sp + i];
			}

			// Put shared data as SIMD share in gate.
			s_x_vec = circ->PutSharedSIMDINGate(last_seg_len, long_arr_a_in_seg, bitlen);
			s_y_vec = circ->PutSharedSIMDINGate(last_seg_len, long_arr_b_in_seg, bitlen);

			// Call the inner product circuit function.
			s_out = inner_product_circuit(s_x_vec, s_y_vec, last_seg_len, circ, two_long_arrays->dim);
		}
		
		// Output the share.
		s_out = circ -> PutOUTGate(s_out, ALL);

		// Execute the party.
		party -> ExecCircuit();

		// Receive final result as an array.
		uint32_t* out_vals;
		uint32_t out_bitlen, out_nvals;
		s_out->get_clear_value_vec(&out_vals, &out_bitlen, &out_nvals);

		// Write current results into final long array
		int cur_res_seg_len;
		
		if (i != seg_num - 1)
		{
			cur_res_seg_len = seg_len / two_long_arrays->dim;
			for(int j=0; j<cur_res_seg_len; j++){
				res_arr[res_sp + j] = out_vals[j] % mod_num;
			}
			res_sp += cur_res_seg_len;
		}
		else
		{
			int last_seg_len = two_long_arrays->long_array_len - (seg_num - 1) * seg_len;
			cur_res_seg_len = last_seg_len / two_long_arrays->dim;
			for(int j=0; j<cur_res_seg_len; j++){
				res_arr[res_sp + j] = out_vals[j] % mod_num;
			}
		}


		cout<<i+1<<"/"<<seg_num<<" of total is done..."<<endl;
		
		delete s_x_vec, s_y_vec, s_out, long_arr_a_in_seg, long_arr_b_in_seg, party, circ, out_vals, out_nvals, out_bitlen;
	}
	return res_arr;
}


int main(int argc, char** argv) {

	// Basic parameters.
	e_role role;
	uint16_t bitlen = 8, nvals = 128, secparam = 128, nthreads = 1;
	uint16_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
	string dir = "/home/chen/Git_repositories/pprbf/src/data/probe/";
	int seg_len_limit = 100000000;

	// Parse command line.
	read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op, &dir);

	seclvl seclvl = get_sec_lvl(secparam);

	// Read csv file part
	long_array* two_long_arrays = new long_array(dir, role);
	cout<<"Long arrays built."<<endl;

	// call inner product routine. set size with cmd-parameter -n <size>
	uint32_t* res_arr_final = general_circuit(role, address, port, seclvl, nvals, bitlen, nthreads, mt_alg, S_ARITH, two_long_arrays, seg_len_limit);
	cout<<"Dot product calculted."<<endl;

	// Write the dot product matrix into csv file.
	csv_writer *csv_to_write = new csv_writer(res_arr_final, two_long_arrays->res_array_length, two_long_arrays->row_nums);
	csv_to_write->write_matrix_into_csv(dir + "./dp_mat.csv");
	cout<<"CSV file written."<<endl;
	
	return 0;
}
