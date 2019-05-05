/**
 \title     ABY Probe
 \author    Huajie Chen
 \copyright ABY Development Team & Huajie Chen
 \brief     This is an implementation of kinds of function realized by ABY framework
*/

// ABY Kernel
#include "../ABY/src/abycore/DJN/djnparty.h"
#include "../ABY/src/abycore/DGK/dgkparty.h"
#include "../ABY/src/abycore/sharing/yaosharing.h"
#include "../ABY/src/abycore/sharing/sharing.h"
#include "../ABY/src/abycore/sharing/yaoclientsharing.h"
#include "../ABY/src/abycore/sharing/boolsharing.h"
#include "../ABY/src/abycore/sharing/splut.h"
#include "../ABY/src/abycore/sharing/yaoserversharing.h"
#include "../ABY/src/abycore/sharing/arithsharing.h"
#include "../ABY/src/abycore/ABY_utils/yaokey.h"
#include "../ABY/src/abycore/ABY_utils/convtypes.h"
#include "../ABY/src/abycore/ABY_utils/ABYconstants.h"
#include "../ABY/src/abycore/circuit/booleancircuits.h"
#include "../ABY/src/abycore/circuit/abycircuit.h"
#include "../ABY/src/abycore/circuit/circuit.h"
#include "../ABY/src/abycore/circuit/arithmeticcircuits.h"
#include "../ABY/src/abycore/circuit/share.h"
#include "../ABY/src/abycore/ot/arithmtmasking.h"
#include "../ABY/src/abycore/aby/abyparty.h"
#include "../ABY/src/abycore/aby/abysetup.h"

//Utility libs
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

#include <math.h>
#include <cassert>
#include "iostream"
using namespace std;

uint32_t basic_calculation(e_role role, uint32_t int_a, uint32_t int_b){
    // Initiation
    string address = (char*) "127.0.0.1";  // IP address
    uint16_t port = 6677;  // Listening port
    seclvl seclvl = LT;  // Long term 
    uint32_t bitlen = 32;  // Maximum bitlen
    uint32_t nthreads = 1;  // Number of threads
    e_mt_gen_alg mg_algo = MT_OT;
    uint32_t maxgates = 1000000;  // Maximum gates
    e_sharing sharing = S_YAO; // Type of sharing: Y

    // Create party, get sharings, build up circuit
    ABYParty* party = new ABYParty(role , (char*) address.c_str(), port , seclvl , bitlen , nthreads, MT_OT, maxgates);
    vector <Sharing*>& sharings = party ->GetSharings ();  // Vector of sharings is obtained.
    Circuit* circ = sharings[sharing]->GetCircuitBuildRoutine ();  // Circuit is obtained according to type: A / B / Y

    // Create shares
    share *s_int_a, *s_int_b, *s_out;

    // Put in gate according to role
    if (role == SERVER)
    {
        s_int_a = circ->PutDummyINGate(bitlen);
        s_int_b = circ->PutINGate(int_b, bitlen, SERVER);
    } else
    {
        // role == CLIENT
        s_int_a = circ->PutINGate(int_a, bitlen, CLIENT);
        s_int_b = circ->PutDummyINGate(bitlen);
    }
    // Perform (a+b) * (a-b)
    share* step1 = circ->PutADDGate(s_int_a, s_int_b);
    share* step2 = circ->PutSUBGate(s_int_a, s_int_b);
    share* step3 = circ->PutSUBGate(s_int_b, s_int_a);
    share* step4 = circ->PutMULGate(step1, step2);
    s_out = step4;
    s_out = circ->PutOUTGate(s_out, ALL);

    party->ExecCircuit();

    uint32_t output = s_out->get_clear_value<uint32_t>(); // Need to write the class of output

    uint32_t true_outcome = (int_a + int_b) * (int_a - int_b);

    cout << "Basic calculation test starts..." << endl;
    cout << "Sharing type: " << get_sharing_name(sharing) << endl;
    cout << "int_a: " << int_a;
    cout << "int_b: " << int_b;
    cout << "Circuit calculated outcome: " << output;
    cout << "True outcome: " << true_outcome;
}
