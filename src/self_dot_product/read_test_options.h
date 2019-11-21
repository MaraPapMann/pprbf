#ifndef READ_TEST_OPTIONS_
#define READ_TEST_OPTIONS_

#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include "../ABY/src/abycore/aby/abyparty.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;


int read_test_options(int32_t* argcp, char*** argvp, string* dir);

#endif