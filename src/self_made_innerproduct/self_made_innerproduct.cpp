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
using namespace std;


// Need input vector xvals & yvals
int32_t inner_product_circuit(e_role role, const std::string& address, uint16_t port, seclvl seclvl,
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

        }

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