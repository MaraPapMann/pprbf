#ifndef __INNERPRODUCT_H_# define __INNERPRODUCT_H_

#include "../../ABY/src/abycore/circuit/booleancircuits.h"

#include "../../ABY/src/abycore/circuit/arithmeticcircuits.h"

#include "../../ABY/src/abycore/circuit/circuit.h"

#include "../../ABY/src/abycore/aby/abyparty.h"

#include "../../ABY/src/abycore/sharing/sharing.h"

#include <math.h>
#include <cassert>
#include <vector>

using namespace std;


int32_t test_inner_product_circuit(e_role role, char * address, uint16_t port, seclvl seclvl,
  uint32_t nvals, uint32_t bitlen, uint32_t nthreads, e_mt_gen_alg mt_alg,
  e_sharing sharing, uint32_t r, uint32_t c);

#endif