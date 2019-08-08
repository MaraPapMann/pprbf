#include "self_dot_product.h"


vector<string> self_dot_product::get_all_file_in_dir()
{
    vector<string> fv;
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string cur_name = dp->d_name;
        if (cur_name.find("split") == string::npos)
        {
            fv.push_back(path+dp->d_name);
        }
    }
    sort(fv.begin(), fv.end());
    vector<string>::const_iterator first = fv.begin() + 2;
    vector<string>::const_iterator last = fv.end();
    vector<string> new_fv(first, last);
    closedir(dirp);
    return new_fv;
}


vector<vector<uint16_t>> self_dot_product::parse_file_as_vec(string file_path)
{
    vector<vector<uint16_t>> parsed_file;
    csv_parser *csv = new csv_parser(file_path, ',');
    for(int i=0; i<csv->nrow; i++){
        vector<uint16_t> temp_vec;
        for(int j=0; j<csv->ncol; j++){
            temp_vec.push_back(csv->array[i][j]);
        }
        parsed_file.push_back(temp_vec);
    }
    delete csv;
    return parsed_file;
}


vector<uint16_t> self_dot_product::calc_self_dp(vector<vector<uint16_t>> parsed_file)
{
    vector<uint16_t> self_dp;
    for(int i=0; i<parsed_file.size(); i++){  // The first vector.
        for(int j=0; j<parsed_file.size(); j++){  // The second vector.
            uint16_t temp_dp = 0;
            for(int k=0; k<parsed_file[0].size(); k++){  // Going through by columns.
                temp_dp = temp_dp + parsed_file[i][k] * parsed_file[j][k];  // Summation.
            }
            self_dp.push_back(temp_dp);
        }
    }
    return self_dp;
}


vector<vector<uint16_t>> self_dot_product::get_self_dp_all()
{
    vector<vector<uint16_t>> self_dp_all;
    for(string file:file_vector){
        vector<vector<uint16_t>> parsed_file = self_dot_product::parse_file_as_vec(file);
        vector<uint16_t> self_dp = self_dot_product::calc_self_dp(parsed_file);
        self_dp_all.push_back(self_dp);
    }
    return self_dp_all;
}


vector<vector<uint16_t>> self_dot_product::split_dp_into_2()
{
    int mod_num = 256;
    vector<vector<uint16_t>> split_dp;
    for(int i=0; i<self_dp.size(); i++)
    {
        vector<uint16_t> split_1, split_2;
        for(int j=0; j<self_dp[i].size(); j++)
        {
            uint16_t temp_rand_int = rand() % mod_num;
            split_1.push_back(temp_rand_int);
            split_2.push_back(mod_num + self_dp[i][j] - temp_rand_int);
        }
        split_dp.push_back(split_1);
        split_dp.push_back(split_2);
    }
    return split_dp;
}


void self_dot_product::output_csv_files(string out_file)
{
    for(int i=0; i<split_dp.size(); i=i+2){
        std::ofstream csv_1;
        csv_1.open(path + out_file + "_" + to_string(i / 2 + 1) + "_split_1" + ".csv");
        for(int j=0; j<split_dp[0].size(); j++){
            csv_1 << split_dp[i][j];
            if (j != split_dp[0].size() - 1)
            {
                csv_1 << ",";  // End of col.
            }
        }
        csv_1.close();

        std::ofstream csv_2;
        csv_2.open(path + out_file + "_" + to_string(i / 2 + 1) + "_split_2" + ".csv");
        for(int j=0; j<split_dp[0].size(); j++){
            csv_2 << split_dp[i+1][j];
            if (j != split_dp[0].size() - 1)
            {
                csv_2 << ",";  // End of col.
            }
        }
        csv_2.close();
    }
}


int main()
{
    self_dot_product *s_dp = new self_dot_product("../data/probe/");
    
    s_dp->output_csv_files("self_dp");
}