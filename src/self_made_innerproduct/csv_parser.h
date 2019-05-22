#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;

class CSVReader
{
	string fileName;
	string delimeter;
 
public:
	CSVReader(string filename, string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }
 
	// Function to fetch data from a CSV File
	vector<vector<uint32_t>> getData();
};