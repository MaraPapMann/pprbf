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

	// Get the number of rows of the csv file.
	int get_nrow();

	// Get the number of columns of the csv file.
	int get_ncol();

	// Parse the data into an array.
	uint16_t** get_data_as_array();
public:
	// Initiator.
	csv_parser(string file_name, char delm = ','):
			file_name(file_name), delimeter(delm)
	{}

	// Number of rows in this file.
	int nrow = csv_parser::get_nrow();

	// Number of columns in this file.
	int ncol = csv_parser::get_ncol();

	// Data array.
	uint16_t** array = csv_parser::get_data_as_array();

};