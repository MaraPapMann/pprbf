#include "read_test_options.h"


int read_test_options(int32_t* argcp, char*** argvp, e_role* role,
	uint16_t* bitlen, uint16_t* nvals, uint16_t* secparam, std::string* address,
	uint16_t* port, int32_t* test_op, string* dir) 
	{
	uint16_t int_role = 0, int_port = 0;

	parsing_ctx options[] =
			{ { (void*) &int_role, T_NUM, "r", "Role: 0/1", true, false },
				{ (void*) nvals, T_NUM, "n",	"Number of elements for inner product", false, false },
				{	(void*) bitlen, T_NUM, "b", "Bit-length, default 32", false, false },
				{ (void*) secparam, T_NUM, "s", "Symmetric Security Bits, default: 128", false, false },
				{	(void*) address, T_STR, "a", "IP-address, default: localhost", false, false },
				{	(void*) &int_port, T_NUM, "p", "Port, default: 7766", false, false },
				{ (void*) test_op, T_NUM, "t", "Single test (leave out for all operations), default: off",
					false, false }, 
				{	(void*) dir, T_STR, "d", "Directory containing .csv files", false, false }
				};

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

	return 0;
}