#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "csv_parser.h"
using namespace std;

/**
 * Outline
 * 1. Parse a .csv as a m*n vector, m and n are respective number of row and column of a .csv.
 * 2. Transform the string in each cell into uint_32 and then replace the original vector.
 * 3. Pass the data to the next function.


/*
 * A class to read data from a csv file.
 */


/**
 * Transform a string number to a integer number.
 * @param: str: string; target string number.
 * return: n: uint32_t; transformed integer nubmer.
 */
uint32_t string_to_uint32t(string str){
    uint32_t n = std::stoi(str);  // Converting format.
    return n;
}


/**
 * Rewrite a 2D string vector to a 2D integer vector.
 * @param: input_vector: vector<vector<string>>; target string vector.
 * return: new_vector: vector<vector<uint32_t>>; rewritten integer vector.
 */
vector<vector<uint32_t>> rewrite_vector_string_to_int(vector<vector<string>> input_vector){
    vector<vector<uint32_t>> new_vector(input_vector.size());  // Initializing
    for (int i = 0; i < input_vector.size(); i++)
    {
        vector<string> cur_vec = input_vector[i];  // Access current vector.
        vector<uint32_t> temp_vec(input_vector[0].size());   // Create a temporary vector to store data.
        for (int j = 0; j < input_vector[0].size(); j++)
        {
            string data = cur_vec[j];  // Access current data.
            uint32_t temp_data = string_to_uint32t(data);  // Convert format
            temp_vec[j] = temp_data;
        }
        new_vector[i] = temp_vec;
    }
    return new_vector;
    
}


vector<vector<uint32_t>> CSVReader::getData()
{
	ifstream file(fileName);
 
	vector<vector<string>> dataList;
 
	string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		vector<string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	// Close the File
	file.close();

    vector<vector<uint32_t>> int_dataList = rewrite_vector_string_to_int(dataList);

	return int_dataList;
}


// Test the functions above
void test(string inputFile){
    // Creating an object of CSVWriter
	CSVReader reader(inputFile);
 
	// Get the data from CSV File
	vector<vector<uint32_t>> dataList = reader.getData();
 
	// Print the content of row by row on screen
	for(vector<uint32_t> vec : dataList)
	{
		for(uint32_t data : vec)
		{
			cout << data << " , ";
		}
		cout << endl;
	}
}
