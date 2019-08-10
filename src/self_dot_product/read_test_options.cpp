#include "read_test_options.h"


int read_test_options(int32_t* argcp, char*** argvp, string* dir) 
	{
	uint16_t int_role = 0, int_port = 0;

	parsing_ctx options[] =
			{ {	(void*) dir, T_STR, "d", "Directory containing .csv files", true, true }
				};

	if (!parse_options(argcp, argvp, options,
			sizeof(options) / sizeof(parsing_ctx))) {
		print_usage(*argvp[0], options, sizeof(options) / sizeof(parsing_ctx));
		std::cout << "Exiting" << std::endl;
		exit(0);
	}

	return 0;
}