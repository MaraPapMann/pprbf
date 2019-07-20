#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include "/home/chen/Git_repositories/pprbf/src/ABY/src/abycore/aby/abyparty.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


int read_test_options(int32_t* argcp, char*** argvp, e_role* role,
	uint16_t* bitlen, uint16_t* nvals, uint16_t* secparam, std::string* address,
	uint16_t* port, int32_t* test_op, string* dir);