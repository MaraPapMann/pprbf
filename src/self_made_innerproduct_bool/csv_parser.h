#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
using namespace std;


/**
 * Create a CSV Reader class
 * @param: fileName: string; the path to the file.
 * @param: delimeter: string; the separator of different cells.
 */
class CSVReader
{
	string fileName;
	string delimeter;
 
/**
 * Parse the csv file as a 2D list
 * @param: filename: string; the path to the file.
 * @param: delimeter: string; the separator of different cells.
 * @return: int_dataList: vector<vector<uint32_t>>; 2D vector containing CSV data.
 */
public:
	CSVReader(string filename, string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }
 
	// Function to fetch data from a CSV File
	vector<vector<uint32_t>> getData();
};