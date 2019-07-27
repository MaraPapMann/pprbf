/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      1.	Parse all csv files in given directory;
 * 		2.	Calculate the dot product and push them into an array;
 * 		3.	Transform the dot product array into a vector, get the dot product matrix and write it into a csv file.
 *  @Input:
 *      1.  role: 0:SERVER, 1:CLIENT;
 * 		2.	dir: directory containing the target csv files.
 *  @Output:
 *      1. write the dot product matrix into csv file.
 */

//Utility libraries.
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

// ABY Party class.
#include "../ABY/src/abycore/aby/abyparty.h"

// ABY Circuit and Sharing.
#include "../ABY/src/abycore/ABY_utils/ABYconstants.h"
#include "../ABY/src/abycore/circuit/booleancircuits.h"
#include "../ABY/src/abycore/circuit/circuit.h"
#include "../ABY/src/abycore/sharing/sharing.h"

// Basic packages.
#include <math.h>
#include <cassert>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <chrono>

// Self-produced codes.
#include "read_test_options.h"
#include "long_array.h"
#include "csv_writer.h"

using namespace std;


share* inner_product_circuit(share *s_x, share *s_y, int num, BooleanCircuit *bc, uint16_t dim) {
	uint16_t c = dim;
	uint16_t r = num / dim;
	// pairwise multiplication of all input values
	s_x = bc->PutANDGate(s_x, s_y); // Now each nval is a value, need to be transposed so that each wire stands for one value.
	
	int e = 1;
	while (e < c)
		e = e << 1;
	e = e >> 1;
	uint32_t * pos1 = new uint32_t[e * r];
	uint32_t * pos2 = new uint32_t[e * r];
	int ind1 = 0;
	int ind2 = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < e; j++) {
		pos1[ind1++] = (i * c) + j;  // The first part of the segmentation.
		}
		// The indices in the second half part.
		for (int j = e; j < c; j++)
		pos2[ind2++] = (i * c) + j;  // The rest of the segmentation.
		for (int j = c; j < (2 * e); j++)
		pos2[ind2++] = num;  // Set the very last index to the "0".

	}

	share * part1 = bc -> PutSubsetGate(s_x, pos1, e * r);
	share * part2 = bc -> PutSubsetGate(s_x, pos2, e * r);

	delete[] pos1;
	delete[] pos2;

	s_x = bc -> PutADDGate(part1, part2);
	e = e >> 1;
	while (e >= 1) {
		uint32_t * p1 = new uint32_t[e * r];
		uint32_t * p2 = new uint32_t[e * r];
		for (int i = 0; i < r; i++) {
		for (int j = 0; j < e; j++) {
			p1[(i * e) + j] = ((i * e * 2) + j);
		}
		for (int j = e; j < (2 * e); j++)
			p2[(i * e) + (j - e)] = (i * e * 2) + j;
		}
		part1 = bc -> PutSubsetGate(s_x, p1, e * r);
		part2 = bc -> PutSubsetGate(s_x, p2, e * r);

		delete[] p1;
		delete[] p2;
		s_x = bc -> PutADDGate(part1, part2);

		e = e >> 1;
	}

	return s_x;
}

// Need input vector xvals & yvals
uint32_t* general_circuit(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
		uint16_t nvals, uint16_t bitlen, uint16_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, long_array* two_long_arrays, int seg_len_limit) {
	
	// Array carrying the results.
	uint32_t* res_arr = new uint32_t[two_long_arrays->res_array_length];
	// Length of one segmentation.
	int seg_len = (two_long_arrays->long_array_len % seg_len_limit / two_long_arrays->dim) * two_long_arrays->dim;
	cout<<"Segmentation Length: "<<seg_len<<endl;
	// Number of segmentations.
	int seg_num = two_long_arrays->long_array_len / seg_len;
	
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
		BooleanCircuit* circ = (BooleanCircuit*) sharings[sharing]->GetCircuitBuildRoutine();
		// Sharings.
		share *s_x_vec, *s_y_vec, *s_out;
		uint32_t* out_vals;
		uint32_t out_bitlen, out_nvals;

		int cur_res_arr_len;
		// Long array a in segmentation.
		uint16_t* long_arr_a_in_seg;
		// Long array b in segmentation.
		uint16_t* long_arr_b_in_seg;
		
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
			delete[] long_arr_a_in_seg;
			delete[] long_arr_b_in_seg;

			// Call the inner product circuit function.
			s_out = inner_product_circuit(s_x_vec, s_y_vec, seg_len, circ, two_long_arrays->dim);

			cur_res_arr_len = seg_len / two_long_arrays->dim;
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
			delete[] long_arr_a_in_seg;
			delete[] long_arr_b_in_seg;

			// Replace PutMULGate with PutANDGate in this specific context.
			s_out = inner_product_circuit(s_x_vec, s_y_vec, last_seg_len, circ, two_long_arrays->dim);
			cur_res_arr_len = last_seg_len / two_long_arrays->dim;
		}
		
		// Output the share.
		s_out = circ -> PutOUTGate(s_out, ALL);

		// Execute the party.
		party -> ExecCircuit();

		// Receive final result as an array.
		s_out->get_clear_value_vec(&out_vals, &out_bitlen, &out_nvals);

		/* 
		// Sum up the products between two vectors into an array.
		uint32_t *cur_res_arr = new uint32_t[cur_res_arr_len];
		for(int l=0; l<cur_res_arr_len; l++){
			int cur_sum = 0;
			for(int m=l*two_long_arrays->dim; m<(l+1)*two_long_arrays->dim; m++){
				cur_sum += out_vals[m];
			}
			cur_res_arr[l] = cur_sum;
		}
		*/

		// Write current results into final long array
		for(int j=0; j<cur_res_arr_len; j++){
			res_arr[res_sp + j] = out_vals[j];
		}
		res_sp += cur_res_arr_len;

		cout<<i+1<<"/"<<seg_num<<" of total is done..."<<endl;

		party->Reset();
		//delete cur_res_arr;

		delete party;
		delete s_x_vec;
		delete s_y_vec;
		delete s_out;
		delete out_vals;
	}
	return res_arr;
}


int main(int argc, char** argv) {

	// Basic parameters.
	e_role role;
	uint16_t bitlen = 1, nvals = 128, secparam = 128, nthreads = 1;
	uint16_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
	string dir = "/home/chen/Git_repositories/pprbf/src/data/probe/";
	int seg_len_limit = 1000000;

	// Parse command line.
	read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op, &dir);
	// Get security level.
	seclvl seclvl = get_sec_lvl(secparam);

	// Start counting time.
	chrono::steady_clock sc;
	auto start = sc.now();

	// Read csv file part
	long_array* two_long_arrays = new long_array(dir, role);
	cout<<"Long arrays built."<<endl;
	cout<<"Long array length: "<<two_long_arrays->long_array_len<<endl;

	// call inner product routine. set size with cmd-parameter -n <size>
	uint32_t* res_arr_final = general_circuit(role, address, port, seclvl, nvals, bitlen, nthreads, mt_alg, S_BOOL, two_long_arrays, seg_len_limit);
	cout<<"Dot product calculted."<<endl;

	// Write the dot product matrix into csv file.
	csv_writer *csv_to_write = new csv_writer(res_arr_final, two_long_arrays->res_array_length, two_long_arrays->row_nums);
	csv_to_write->write_matrix_into_csv(dir + "./dp_mat.csv");
	cout<<"CSV file written."<<endl;
	delete two_long_arrays;
	delete[] res_arr_final;
	delete csv_to_write;

	// End counting time;
	auto end = sc.now();
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // measure time span between start & end
   	cout<<"Operation took: "<<time_span.count()<<" seconds...";
	
	return 0;
}
