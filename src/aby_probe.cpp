/**
 \title     ABY Probe
 \author    Huajie Chen
 \copyright ABY
 \brief     This is an implementation imitating "millionaire_prob.cpp" in ABY framework only for understanding.
*/

#include "./ABY/src/examples/millionaire_prob/common/millionaire_prob.h"
#include "./ABY/src/abycore/circuit/booleancircuits.h"
#include "./ABY/src/abycore/sharing/sharing.h"

/**
 * Test millionaire problem circuit
 * In:
 * Out:
 * intrep.:
 */
int32_t test_billionaire_prob_circuit(e_role role, const std::string& address, uint16_t port, seclvl seclvl, 
        uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg, e_sharing sharing) {
    
    // 1. Create ABY party -- basis
    // TODO: Figure out what is ABY party. List interpretation of all parameters used in this function.
    ABYParty* party = new ABYParty(role, address, port, seclvl, bitlen, nthreads, mt_alg);
    /**
     * Path: ./src/ABY/src/abycore/aby/abyparty.cpp
     * e_role: enum: SERVER, CLIENT, ALL
     * const std::string&: a std::string will not change and pass by reference (not pointer, must have a actual object itself)
     * uint16_t: Unassigned 16-bit integer
     * seclvl: Security level
     * nvals: Number of Value
     * bitlen: Bit length of the input
     * nthreads: Number of threads
     * mt_alg: The algo for generation of multiplication triples
     * sharing: Sharing type object
     */

    // 2. Manage all possible sharing type
    // TODO: Figure out std::vector
    // TODO: Figure out Sharing*
    // TODO: Figure out ->
    // TODO: Figure out GetSharings()
    std::vector<Sharing*>& sharings = party->GetSharings();
    // -> is used for accessing variables or functions using pointer (RAM Management)
    /**
     * std::vector<x> n: Create a vector n containing x
     * Path to Sharing class: ./src/ABY/src/abycore/sharing/sharing.cpp
     * ->: Call methods of a class when using pointer
     * GetSharing(): Return m_vSharings
     */

    // 3. Create circuit object
    // TODO: Figure out Circuit*
    // TODO: Figure out sharings[sharing]
    // TODO: Figure out GetCircuitBuildRoutine()
    Circuit* circ = sharings[sharing]->GetCircuitBuildRoutine();
    /**
     * Circuit: Class, path: ./src/ABY/src/abycore/sharing/sharing.cpp
     * sharings[sharing]: Previously defined in this file
     * GetCircuitBuildRoutine(): Return m_cBoolCircuit
     */

    // 4. Create share objects
    share *s_alice_money, *s_bob_money, *s_out;

    // 5. Initialize random values and output
    uint32_t alice_money, bob_money, output;
    srand(time(NULL));  // makes use of the computer's internal clock to control the choice of the seed.
    alice_money = rand();
    bob_money = rand();

    // 6. Load the generated random value (money) into the respective share objects using PutINGate()
    // TODO: Figure out PutDummyINGate()
    // TODO: Figure out PutINGate()
    if(role == SERVER) {  // role == 0
        s_alice_money = circ->PutDummyINGate(bitlen);  // Give only dummy bitlen to the share
        s_bob_money = circ->PutINGate(bob_money, bitlen, SERVER);  // Transform the raw data then pump it into the share
    } else
    {
        // role == 1 (Client)
        s_alice_money = circ->PutINGate(alice_money, bitlen, CLIENT);
        s_bob_money = circ->PutDummyINGate(bitlen);
    }
    /**
     * virtual share* PutINGate(uint32_t val, uint32_t bitlen, e_role role) = 0;
     * virtual share* PutDummyINGate(uint32_t bitlen) = 0;
     */
    
    // 7. Build the circuit
    // TODO: Figure out BuildMillionaireProbCircuit()
    // TODO: Figure out BooleanCircuit()
    s_out = BuildMillionaireProbCircuit(s_alice_money, s_bob_money, (BooleanCircuit*) circ);

    // 8. Write output based on role
    s_out = circ->PutOUTGate(s_out, ALL);

    // 9. Execute the circuit
    party->ExecCircuit();

    // 10. Output the value as integer
    // TODO: Look into output
    output = s_out->get_clear_value<uint32_t>();
	std::cout << "Testing Millionaire's Problem in " << get_sharing_name(sharing)
				<< " sharing: " << std::endl;
	std::cout << "\nAlice Money:\t" << alice_money;
	std::cout << "\nBob Money:\t" << bob_money;
	std::cout << "\nCircuit Result:\t" << (output ? ALICE : BOB);  // If output == True, print Alice; else, print Bob
	std::cout << "\nVerify Result: \t" << ((alice_money > bob_money) ? ALICE : BOB)  // If alice_money > bob_money, print Alice; Vice versa.
				<< "\n";
    /**
     * Circuit Result is the one obtained from the circuit, may not always be right.
     * Verify Result is therefore used to verify the circuit result.
     */

	delete party;
	return 0;
}

share* BuildMillionaireProbCircuit(share *s_alice, share *s_bob, BooleanCircuit *bc) {

	share* out;

	/** Calling the greater than equal function in the Boolean circuit class.*/
	out = bc->PutGTGate(s_alice, s_bob);

	return out;
}