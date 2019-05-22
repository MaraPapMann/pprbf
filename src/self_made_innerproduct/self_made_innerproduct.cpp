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


share* BuildInnerProductCircuit(share *s_x, share *s_y, uint32_t num, ArithmeticCircuit *ac) {
		uint32_t i;

		// pairwise multiplication of all input values
		s_x = ac->PutMULGate(s_x, s_y);

		// split SIMD gate to separate wires (size many)
		s_x = ac->PutSplitterGate(s_x);

		// add up the individual multiplication results and store result on wire 0
		// in arithmetic sharing ADD is for free, and does not add circuit depth, thus simple sequential adding
		for (i = 1; i < num; i++) {
			s_x->set_wire_id(0, ac->PutADDGate(s_x->get_wire_id(0), s_x->get_wire_id(i)));
		}

		// discard all wires, except the addition result
		s_x->set_bitlength(1);

		return s_x;
}

// Need input vector xvals & yvals
int32_t inner_product_circuit(e_role role, const std::string& address, uint32_t port, seclvl seclvl,
		uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
		e_sharing sharing, vector<uint32_t> xvals, vector<uint32_t> yvals) {
    
    ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads,
			mt_alg);

    std::vector<Sharing*>& sharings = party->GetSharings();

    ArithmeticCircuit* circ =
			(ArithmeticCircuit*) sharings[sharing]->GetCircuitBuildRoutine();

    share *s_x_vec, *s_y_vec, *s_out;
    uint32_t num = xvals.size();

    s_x_vec = circ->PutSIMDINGate(num, xvals.data(), 32, SERVER);
	  s_y_vec = circ->PutSIMDINGate(num, yvals.data(), 32, CLIENT);

    s_out = BuildInnerProductCircuit(s_x_vec, s_y_vec, num,
			(ArithmeticCircuit*) circ);

		s_out = circ -> PutOUTGate(s_out, ALL);

		party -> ExecCircuit();

		uint32_t output = s_out -> get_clear_value<uint32_t>();

		uint32_t v_sum = 0;

		for (uint32_t i = 0; i < xvals.size(); i++)
		{
				uint32_t x = xvals[i];
				uint32_t y = yvals[i];
				v_sum += x*y;
		}
		
		std::cout << "\nCircuit Result: " << output;
		std::cout << "\nVerification Result: " << v_sum << std::endl;

		delete s_x_vec;
		delete s_y_vec;
		delete party;

		return 0;
        }

int32_t read_test_options(int32_t* argcp, char*** argvp, e_role* role,
		uint32_t* bitlen, uint32_t* nvals, uint32_t* secparam, std::string* address,
		uint32_t* port, int32_t* test_op) {

		uint32_t int_role = 0, int_port = 0;

		parsing_ctx options[] =
				{ { (void*) &int_role, T_NUM, "r", "Role: 0/1", true, false },
					{ (void*) nvals, T_NUM, "n",	"Number of elements for inner product", false, false },
					{	(void*) bitlen, T_NUM, "b", "Bit-length, default 32", false, false },
					{ (void*) secparam, T_NUM, "s", "Symmetric Security Bits, default: 128", false, false },
					{	(void*) address, T_STR, "a", "IP-address, default: localhost", false, false },
					{	(void*) &int_port, T_NUM, "p", "Port, default: 7766", false, false },
					{ (void*) test_op, T_NUM, "t", "Single test (leave out for all operations), default: off",
						false, false } };

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

		return 1;
}


int main(int argc, char** argv) {

		e_role role;
		uint32_t bitlen = 16, nvals = 128, secparam = 128, nthreads = 1;
		uint32_t port = 7766;
		std::string address = "127.0.0.1";
		int32_t test_op = -1;
		e_mt_gen_alg mt_alg = MT_OT;

		read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op);

		seclvl seclvl = get_sec_lvl(secparam);

		vector<uint32_t> x_vec, y_vec;
		//CSVReader x_csv("./x.csv"), y_csv("./y.csv");
		//x_vec = x_csv.getData()[0];
		//y_vec = y_csv.getData()[0];
		x_vec.push_back(1);
		y_vec.push_back(2);

		// call inner product routine. set size with cmd-parameter -n <size>
		inner_product_circuit(role, address, port, seclvl, 1, 32, nthreads, mt_alg, S_ARITH, x_vec, y_vec);

		return 0;
}

