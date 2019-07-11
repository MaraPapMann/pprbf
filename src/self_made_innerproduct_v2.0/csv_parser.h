#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;


class csv_parser
{
private:
	string file_name;
	char delimeter;

public:
	csv_parser(string file_name, char delm = ','):
			file_name(file_name), delimeter(delm)
	{}

	// To get the number of rows of the csv file.
	int get_nrow();

	// To get the number of columns of the csv file.
	int get_ncol();

	//
	uint32_t** get_data_as_array();

	int nrow = csv_parser::get_nrow();
	int ncol = csv_parser::get_ncol();
	uint32_t** array = csv_parser::get_data_as_array();
};