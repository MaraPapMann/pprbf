/**
 \title     ABY Probe
 \author    Huajie Chen
 \copyright ABY Development Team
 \brief     This is an implementation imitating "millionaire_prob.cpp" in ABY framework only for understanding.
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

uint32_t test_billionaire_prob_circuit(e_role role){
    // Initiation
    string address = (char*) "127.0.0.1";  // IP address
    uint16_t port = 6677;  // Listening port
    seclvl seclvl = LT;  // Long term 
    uint32_t bitlen = 32;  // Maximum bitlen
    uint32_t nthreads = 2;  // Number of threads
    e_mt_gen_alg mg_algo = MT_OT;
    uint32_t maxgates = 4000000;  // Maximum gates
    e_sharing sharing = S_YAO;

    // Setup
		ABYParty* party = new ABYParty(role , (char*) address.c_str(), port , seclvl , bitlen , nthreads, MT_OT, maxgates);
		vector <Sharing*>& sharings = party ->GetSharings ();  // Vector of sharings is obtained.
		Circuit* circ = sharings[sharing]->GetCircuitBuildRoutine ();  // Circuit is obtained according to type: A / B / Y

    // Fake Money
    srand(666);
    uint32_t chen_money = rand();
    uint32_t huajie_money = rand();

    // Build up shares
    share *s_chen_money, *s_huajie_money, *s_out;

    // Put in gate according to role
    if(role == SERVER) {
		s_chen_money = circ->PutDummyINGate(bitlen);
		s_huajie_money = circ->PutINGate(huajie_money, bitlen, SERVER);
	} else { //role == CLIENT
		s_chen_money = circ->PutINGate(chen_money, bitlen, CLIENT);
		s_huajie_money = circ->PutDummyINGate(bitlen);
	}

    // Get 
    s_out = circ ->PutGTGate(s_chen_money , s_huajie_money);  // s_chen_money > s_huajie_money ?

    s_out = circ->PutOUTGate(s_out, ALL);

    party ->ExecCircuit ();
    //uint32_t output = s_out ->get_clear_value <uint32_t >(); // the output can be processed here ...

    uint32_t output = s_out->get_clear_value<uint32_t>();

	std::cout << "Testing Billionaire's Problem in " << get_sharing_name(sharing) << " sharing: " << std::endl;
	std::cout << "\nChen Money:\t" << chen_money;
	std::cout << "\nHuajie Money:\t" << huajie_money;
	std::cout << "\nCircuit Result:\t" << (output ? "Chen" : "Huajie");
	std::cout << "\nVerify Result: \t" << ((chen_money > huajie_money) ? "Chen" : "Huajie")
				<< "\n";

	delete party;
	return output;
}

// Copy from the original code
int32_t read_test_options(int32_t* argcp, char*** argvp, e_role* role,
		uint32_t* bitlen, uint32_t* nvals, uint32_t* secparam, std::string* address,
		uint16_t* port, int32_t* test_op) {

	uint32_t int_role = 0, int_port = 0;
	bool useffc = false;

	parsing_ctx options[] =
			{ { (void*) &int_role, T_NUM, "r", "Role: 0/1", true, false }, {
					(void*) nvals, T_NUM, "n",
					"Number of parallel operation elements", false, false }, {
					(void*) bitlen, T_NUM, "b", "Bit-length, default 32", false,
					false }, { (void*) secparam, T_NUM, "s",
					"Symmetric Security Bits, default: 128", false, false }, {
					(void*) address, T_STR, "a",
					"IP-address, default: localhost", false, false }, {
					(void*) &int_port, T_NUM, "p", "Port, default: 7766", false,
					false }, { (void*) test_op, T_NUM, "t",
					"Single test (leave out for all operations), default: off",
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
		assert(int_port < 1 << (sizeof(uint16_t) * 8));
		*port = (uint16_t) int_port;
	}

	//delete options;

	return 1;
}

int main(int argc, char** argv){
    cout << "\nABY Probe Start...\n" << endl;
    e_role role;
	uint32_t bitlen = 32, nvals = 31, secparam = 128, nthreads = 1;
	uint16_t port = 7766;
	std::string address = "127.0.0.1";
	int32_t test_op = -1;
	e_mt_gen_alg mt_alg = MT_OT;
    read_test_options(&argc, &argv, &role, &bitlen, &nvals, &secparam, &address,
			&port, &test_op);

    test_billionaire_prob_circuit(role);

    return 0;
}
