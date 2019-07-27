#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>

 //ABY Party class
#include "../ABY/src/abycore/aby/abyparty.h"
#include "common/innerproduct.h"

#include <string>
using namespace std;

int32_t read_test_options(int32_t * argcp, char ** * argvp, e_role * role,
  uint32_t * bitlen, uint32_t * rows, uint32_t * columns, uint32_t * secparam, string * address,
  uint16_t * port, int32_t * test_op) {

  uint32_t int_role = 0, int_port = 0;

  parsing_ctx options[] = {
    {
      (void * ) & int_role, T_NUM, "r", "Role: 0/1", true, false
    },
    {
      (void * ) rows,
      T_NUM,
      "x",
      "Number of rows",
      false,
      false
    },
    {
      (void * ) columns,
      T_NUM,
      "y",
      "Number of columns",
      false,
      false
    },
    {
      (void * ) bitlen,
      T_NUM,
      "b",
      "Bit-length, default 32",
      false,
      false
    },
    {
      (void * ) secparam,
      T_NUM,
      "s",
      "Symmetric Security Bits, default: 128",
      false,
      false
    },
    {
      (void * ) address,
      T_STR,
      "a",
      "IP-address, default: localhost",
      false,
      false
    },
    {
      (void * ) & int_port,
      T_NUM,
      "p",
      "Port, default: 7766",
      false,
      false
    },
    {
      (void * ) test_op,
      T_NUM,
      "t",
      "Single test (leave out for all operations), default: off",
      false,
      false
    }
  };

  if (!parse_options(argcp, argvp, options,
      sizeof(options) / sizeof(parsing_ctx))) {
    print_usage( * argvp[0], options, sizeof(options) / sizeof(parsing_ctx));
    cout << "Exiting" << endl;
    exit(0);
  }

  assert(int_role < 2);
  * role = (e_role) int_role;

  if (int_port != 0) {
    assert(int_port < 1 << (sizeof(uint16_t) * 8));
    * port = (uint16_t) int_port;
  }

  return 1;
}

int main(int argc, char ** argv) {

  e_role role;
  uint32_t bitlen = 16, rows = 300, columns = 1024, secparam = 128, nthreads = 1;
  uint16_t port = 7766;
  string address = "127.0.0.1";
  int32_t test_op = -1;
  e_mt_gen_alg mt_alg = MT_OT;

  read_test_options( & argc, & argv, & role, & bitlen, & rows, & columns, & secparam, & address, & port, & test_op);

  seclvl seclvl = get_sec_lvl(secparam);

  // call inner product routine. set size with cmd-parameter -n <size>
  test_inner_product_circuit(role, (char * ) address.c_str(), port, seclvl, 1, bitlen, nthreads, mt_alg, S_ARITH, rows, columns);

  return 0;
}