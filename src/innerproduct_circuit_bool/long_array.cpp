#include "long_array.h"


vector<string> long_array::get_all_file_in_dir()
{
    vector<string> fv;
    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        string cur_name = dp->d_name;
        if (role == SERVER)
        {
            if (cur_name.find("split_1") != string::npos)
            {
                fv.push_back(path+dp->d_name);
            }   
        }
        else
        {
            if (cur_name.find("split_2") != string::npos)
            {
                fv.push_back(path+dp->d_name);
            }   
        }
    }
    sort(fv.begin(), fv.end());
    closedir(dirp);
    return fv;
}


int long_array::get_dim(){
    csv_parser* temp_csv = new csv_parser(file_vector[0], ',');
    return temp_csv->ncol;
    delete temp_csv;
}


int long_array::get_one_seg_len(string file_a, string file_b){
    csv_parser* csv_a = new csv_parser(file_a, ',');
    csv_parser* csv_b = new csv_parser(file_b, ',');
    int one_seg_len = dim * csv_a->nrow * csv_b->nrow;
    return one_seg_len;
    delete csv_a, csv_b;
}


int long_array::get_long_array_len(){
    int long_arr_len = 0;
    for(int i=0; i<file_vector.size(); i++){
        string file_a = file_vector[i];
        for(int j=i; j<file_vector.size(); j++){
            string file_b = file_vector[j];
            long_arr_len = long_arr_len + get_one_seg_len(file_a, file_b);
        }
    }
    return long_arr_len;  // For PutSUBSETGate.
}


uint16_t* long_array::get_long_arr_a(){
    uint16_t* long_arr_a = new uint16_t[long_array_len + 1];  // Cannot directly create an array for too large size.
    int sp = 0;
    for(int i=0; i<file_vector.size(); i++){
        string file_a = file_vector[i];
        csv_parser* csv_a = new csv_parser(file_a, ',');
        for(int j=i; j<file_vector.size(); j++){
            string file_b = file_vector[j];
            csv_parser* csv_b = new csv_parser(file_b, ',');
            for(int k=0; k<csv_a->nrow; k++){
                for(int l=0; l<csv_b->nrow; l++){
                    for(int m=0; m<dim; m++){
                        long_arr_a[sp + l * dim + m] = csv_a->array[k][m];
                    }
                }
                sp += csv_b->nrow * dim;
            }
            delete csv_b;
        }
        delete csv_a;
    }
    long_arr_a[long_array_len] = 0;
    return long_arr_a;
}


uint16_t* long_array::get_long_arr_b(){
    uint16_t* long_arr_b = new uint16_t[long_array_len + 1];
    int sp = 0;
    for(int i=0; i<file_vector.size(); i++){
        string file_a = file_vector[i];
        csv_parser* csv_a = new csv_parser(file_a, ',');
        for(int j=i; j<file_vector.size(); j++){
            string file_b = file_vector[j];
            csv_parser* csv_b = new csv_parser(file_b, ',');
            for(int k=0; k<csv_a->nrow; k++){
                for(int l=0; l<csv_b->nrow; l++){
                    for(int m=0; m<dim; m++){
                        long_arr_b[sp + l * dim + m] = csv_b->array[l][m];
                    }
                }
                sp += csv_b->nrow * dim;
            }
            delete csv_b;
        }
        delete csv_a;
    }
    long_arr_b[long_array_len] = 0;
    return long_arr_b;
}


vector<int> long_array::get_row_nums_vec(){
    vector<int> row_nums;
    for(string file:file_vector){
        csv_parser *temp_csv = new csv_parser(file, ',');
        row_nums.push_back(temp_csv->nrow);
    }
    return row_nums;
}

/* 
int main()
{
    string path = "/home/chen/Git_repositories/pprbf/src/data/probe/";
    e_role role = SERVER;
    long_array* long_arr = new long_array(path, role);
    for(string file:long_arr->file_vector){
        cout<<file<<", "<<endl;
    }
    cout<<"dim: "<<long_arr->dim<<endl;
    cout<<"one long array length: "<<long_arr->long_array_len<<endl;
    
    
    for(int i=0; i<long_arr->dim * 2; i++){
        cout<<long_arr->long_array_a[i]<<", ";
    }
    cout<<endl;
    for(int i=0; i<long_arr->long_array_len; i++){
        cout<<long_arr->long_array_b[i]<<", ";
    } 
    
    return 0;
}
*/