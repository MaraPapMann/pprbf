#include "self_dot_product_vector.h"


vector<string> self_dot_product_vector::get_all_file_in_dir()
{
    vector<string> fv;
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string cur_name = dp->d_name;
        if (role == SERVER)
        {
            if (cur_name.find("split_1") != string::npos && cur_name.find("self_dp") != string::npos)
            {
                fv.push_back(path+dp->d_name);
            }   
        }
        else
        {
            if (cur_name.find("split_2") != string::npos && cur_name.find("self_dp") != string::npos)
            {
                fv.push_back(path+dp->d_name);
            }   
        }
    }
    sort(fv.begin(), fv.end());
    closedir(dirp);
    return fv;
}


vector<int> self_dot_product_vector::get_dim_vec()
{
    vector<int> dim_vec;
    for(int i=0; i<file_vector.size(); i++)
    {
        csv_parser* temp_csv = new csv_parser(file_vector[0], ',');
        dim_vec.push_back(temp_csv->ncol);   
        delete temp_csv;
    }
    return dim_vec;
}


vector<uint16_t> self_dot_product_vector::get_long_vec()
{
    vector<uint16_t> long_vec;  // Cannot directly create an array for too large size.
    for(int i=0; i<file_vector.size(); i++){
        string file = file_vector[i];
        csv_parser* csv = new csv_parser(file, ',');
        for(int j=0; j<csv->nrow; i++)
        {
            for(int k=0; k<dim_vec[i]; k++)
            {
                long_vec.push_back(csv->array[j][k]);
            }
        }
        delete csv;
    }
    return long_vec;
}


int self_dot_product_vector::get_self_dp_vec_len()
{
    int self_dp_vec_len = 0;
    for(int i=0; i<dim_vec.size(); i++)
    {
        self_dp_vec_len = self_dp_vec_len + dim_vec[i];
    }
    return self_dp_vec_len;
}