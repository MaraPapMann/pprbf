#include "vector_process.h"
#include "csv_parser.h"


vector<uint32_t> aggregate_vector_1st(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
		int i = vec_a.size();
		int j = vec_a[0].size();
		int k = vec_b.size();
		vector<uint32_t> vec_1st;
		for (vector<uint32_t> vec:vec_a)
		{
			for (int l = 0; l < k; l++)
			{
				vec_1st.insert(vec_1st.end(), vec.begin(), vec.end());
			}
		}
		return vec_1st;
}


vector<uint32_t> aggregate_vector_2nd(vector<vector<uint32_t>> vec_a, vector<vector<uint32_t>> vec_b){
		int i = vec_a.size();
		int j = vec_a[0].size();
		int k = vec_b.size();
		vector<uint32_t> vec_2nd;
		for (int l = 0; l < i; l++)
		{
			for (vector<uint32_t> vec:vec_b)
			{
				vec_2nd.insert(vec_2nd.end(), vec.begin(), vec.end());
			}
		}
		return vec_2nd;
}


vector<string> get_all_file_in_dir(string path, e_role role){
	vector<string> file_vec;
  for (const auto & entry : fs::directory_iterator(path))
	{
		string cur_file = entry.path();
		if (role == SERVER)
		{
			if (cur_file.find("split_1") != string::npos){
				file_vec.push_back(cur_file);
			}
		}
		else // role == CLIENT
		{
			if (cur_file.find("split_2") != string::npos){
				file_vec.push_back(cur_file);
			}
		}
	}
	sort(file_vec.begin(), file_vec.end());
	return file_vec;
}


vector<uint32_t> generate_1st_long_vector_for_all_files_in_dir(vector<string> file_vec){
		vector<uint32_t> vec_to_return;
		for (int i = 0; i < file_vec.size(); i++)
		{
			CSVReader x_csv(file_vec[i]);
			vector<vector<uint32_t>> vec_a = x_csv.getData();
			for (int j = i; j < file_vec.size(); j++)
			{
				CSVReader y_csv(file_vec[j]);
				vector<vector<uint32_t>> vec_b = y_csv.getData();
				vector<uint32_t> temp_vec = aggregate_vector_1st(vec_a, vec_b);
				vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
			}
		}
		return vec_to_return;
}


vector<uint32_t> generate_2nd_long_vector_for_all_files_in_dir(vector<string> file_vec){
		vector<uint32_t> vec_to_return;
		for (int i = 0; i < file_vec.size(); i++)
		{
			CSVReader x_csv(file_vec[i]);
			vector<vector<uint32_t>> vec_a = x_csv.getData();
			for (int j = i; j < file_vec.size(); j++)
			{
				CSVReader y_csv(file_vec[j]);
				vector<vector<uint32_t>> vec_b = y_csv.getData();
				vector<uint32_t> temp_vec = aggregate_vector_2nd(vec_a, vec_b);
				vec_to_return.insert(vec_to_return.end(), temp_vec.begin(), temp_vec.end());
			}
		}
		return vec_to_return;
}


int get_dimension_of_2dvector(vector<vector<uint32_t>> vec){
	return vec[0].size();
}