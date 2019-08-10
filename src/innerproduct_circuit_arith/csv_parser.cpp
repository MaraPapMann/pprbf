#include "csv_parser.h"

/**
 * Outline
 * 1. Parse a .csv as a m*n vector, m and n are respective number of row_num and column of a .csv.
 * 2. Transform the string in each cell into uint_32 and then replace the original vector.
 * 3. Pass the data to the next function.


/*
 * A class to read data from a csv file.
 */


int csv_parser::get_nrow(){
	int row_num;
	ifstream file(file_name);
    string line;
	row_num = 0;
	while (getline(file, line))  // Iterate if there is still row.
	{
		row_num = row_num + 1;  // Counting row number one by one.
	}
	return row_num;
}


int csv_parser::get_ncol(){
	ifstream file(file_name);
    string line;
	int col_num = 0;
	while (getline(file, line))  // Iterate if there is still row.
	{
		istringstream iss(line);
		string result;
		while (getline(iss, result, delimeter))  // Iterate if there is still column.
		{
			col_num = col_num + 1;  // Counting column number one by one.
		}
		break;
	}
	return col_num;
}


uint16_t** csv_parser::get_data_as_array(){
	ifstream file(file_name);
    string line;
	uint16_t** data_arr;
	data_arr = new uint16_t*[nrow];  // Initiating data array 2D using nrow as length.
	for(int i=0; i<nrow; i++){
		data_arr[i] = new uint16_t[ncol];  // Initiating data array 1D using ncol as length.
	}

	int a = 0, b = 0;
	while (getline(file, line))
	{
		istringstream iss(line);
		string result;
		while (getline(iss, result, delimeter))
		{
			data_arr[a][b] = stoi(result.c_str());  // Fill the 2D array with integers(converted from strings).
			b = b + 1;
		}
		a = a + 1;
		b = 0;
	}

	return data_arr;
}

/* 
Testing
int main(){
	csv_parser* csv_a = new csv_parser("/home/chen/Git_repositories/pprbf/src/data/probe/a_encoded_test_seq.txt_split_1.csv", ',');
	cout<<"row number: "<<csv_a->nrow<<endl;
	cout<<"col number: "<<csv_a->ncol<<endl;
	cout<<csv_a->array[csv_a->nrow-1][csv_a->ncol-1]<<endl;
	return 0;
}
*/
