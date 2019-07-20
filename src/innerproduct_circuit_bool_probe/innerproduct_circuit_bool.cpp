/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      1.	
 *  @Input:
 *      1.  
 *  @Output:
 *      1.  
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

// Self-produced code.
#include "read_test_options.h"

using namespace std;

int main(int argc, char **argv)
{
    e_role role;
	uint16_t bitlen = 1, nvals = 128, secparam = 128, nthreads = 1;
	uint16_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
	string dir = "../probe_data/";
	int seg_len_limit = 100000000;

    vector<uint32_t> a1, a2, b1, b2;
    a1 = {1, 1, 1, 1};
    a2 = {0, 1, 0, 1};
    b1 = {0, 0, 0, 0};
    b2 = {1, 0, 0, 1};

	// Parse command line.
	read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address, &port, &test_op, &dir);

	seclvl seclvl = get_sec_lvl(secparam);

    // Initiation of the ABY party.
    ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);
    // Get sharings.
    vector<Sharing*>& sharings = party->GetSharings();
    // Build the corresponding circuit according to the sharing type.
    BooleanCircuit* circ = (BooleanCircuit*) sharings[S_BOOL]->GetCircuitBuildRoutine();

    share *s_x, *s_y, *s_out;
    if (role == SERVER)
    {
        s_x = circ -> PutSharedSIMDINGate(3, a1.data(), bitlen);
        s_y = circ -> PutSharedSIMDINGate(3, b1.data(), bitlen);
    }
    else  // role == CLIENT
    {
        s_x = circ -> PutSharedSIMDINGate(3, a2.data(), bitlen);
        s_y = circ -> PutSharedSIMDINGate(3, b2.data(), bitlen);
    }
    
    s_x = circ->PutSplitterGate(s_x);
    s_y = circ->PutSplitterGate(s_y);
    s_out = circ->PutANDGate(s_x, s_y);

    s_out = circ->PutOUTGate(s_out, ALL);

    party -> ExecCircuit();

    uint32_t *out_vals, out_bitlen, out_nvals;
    s_out -> get_clear_value_vec(&out_vals, &out_bitlen, &out_nvals);

    for(int i=0; i<a1.size(); i++){
        cout<<out_vals[i]<<", ";
    }

    party->Reset();
    delete s_x;
    delete s_y;
    delete s_out;
    delete party;
    
    return 0;
}
