#include "csv_writer.h"


vector<uint32_t> csv_writer::from_array_to_vector(uint32_t *res_array, int array_length){
    vector<uint32_t> res_vec;
    for(int i=0; i<array_length; i++){
        res_vec.push_back(res_array[i]);
    }
    return res_vec;
}


vector<int> csv_writer::get_section_vec(vector<int> row_nums){
    vector<int> section_vec;
    for(int i=0; i<row_nums.size(); i++){
        int sum = 0;
        int row_num_a = row_nums[i];
        for(int j=i; j<row_nums.size(); j++){
            int row_num_b = row_nums[j];
            sum += row_num_a * row_num_b;
        }
        section_vec.push_back(sum);
    }
    return section_vec;
}


vector<vector<int>> csv_writer::get_subsection_vec(vector<int> row_nums){
    vector<vector<int>> subsection_vec;
    for(int i=0; i<row_nums.size(); i++){
        vector<int> temp_vec;
        int row_num_a = row_nums[i];
        for(int j=i; j<row_nums.size(); j++){
            int row_num_b = row_nums[j];
            temp_vec.push_back(row_num_a * row_num_b);
        }
        subsection_vec.push_back(temp_vec);
    }
    return subsection_vec;
}


vector<vector<uint32_t>> csv_writer::splice_res_vec_into_sections(vector<uint32_t> res_vec, vector<int> section_vec){
    vector<vector<uint32_t>> res_vec_in_sections;
    int sp = 0;
    for(int section_len:section_vec){
        int ep = sp + section_len;
        vector<uint32_t> temp_vec;
        for(int i=sp; i<ep; i++){
            uint32_t cur_cell = res_vec[i];
            temp_vec.push_back(cur_cell);
        }
        res_vec_in_sections.push_back(temp_vec);
        sp = sp + section_len;
    }
    return res_vec_in_sections;
}


vector<vector<vector<uint32_t>>> csv_writer::splice_res_vec_in_sections_into_subsections(vector<vector<uint32_t>> res_vec_in_sections,
                                                                             vector<vector<int>> subsection_vec){
    vector<vector<vector<uint32_t>>> res_vec_in_subsections;
    for(int i=0; i<subsection_vec.size(); i++){
        vector<int> section = subsection_vec[i];  // DP index
        int sp = 0;  // Loop starts
        vector<vector<uint32_t>> temp_section;
        vector<uint32_t> res_section = res_vec_in_sections[i];  // DP section
        for(int subsection:section){
            int ep = sp + subsection;
            vector<uint32_t> temp_subsection;
            for(int k=sp; k<ep; k++){
                uint32_t cur_res = res_section[k];
                temp_subsection.push_back(cur_res);
            }
            temp_section.push_back(temp_subsection);
            sp = sp + subsection;  // Loop ends
        }
        res_vec_in_subsections.push_back(temp_section);
    }
    return res_vec_in_subsections;
}


vector<vector<uint32_t>> csv_writer::sorting_res_vec(vector<int> row_nums, 
                    vector<vector<vector<uint32_t>>> res_vec_in_subsections){
    vector<vector<uint32_t>> sorted_res_vec;  // Output initialization.

    // Get the rank of the dot product matrix.
    int dp_rank = 0;  
    for(int row_num:row_nums){
        dp_rank = dp_rank + row_num;
    }

    //
    for(int i=0; i<res_vec_in_subsections.size(); i++){
        vector<vector<uint32_t>> cur_section = res_vec_in_subsections[i];  // Current section.
        int sp_idx = 0;
        for(int m=0; m<row_nums[i]; m++){  // Create several sorted vector to take in the values orderedly.
            vector<uint32_t> sorted_vector;  // Sorted vector created.
            for(int j=0; j<cur_section.size(); j++){
                vector<uint32_t> cur_subsection = cur_section[j];
                int row_num = row_nums[j+i];  // HARD POINT!!!
                int sp = sp_idx*row_num;
                int ep = sp + row_num;
                for(int k=sp; k<ep; k++){
                    sorted_vector.push_back(cur_subsection[k]);
                }
            }
            sorted_res_vec.push_back(sorted_vector);
            sp_idx++;
        }
    }
    return sorted_res_vec;
}


vector<vector<uint32_t>> csv_writer::get_dp_matrix(vector<vector<uint32_t>> sorted_res_vec){
    // Initialization
    int dim = sorted_res_vec[0].size();
    vector<vector<uint32_t>> dp_mat(dim, vector<uint32_t>(dim, 0));

    // Filling half of the matrix
    for(int i=0; i<dp_mat.size(); i++){
        vector<uint32_t> cur_row = dp_mat[i];
        int norm_dist = sorted_res_vec[0].size() - sorted_res_vec[i].size();
        for(int j=i; j<cur_row.size(); j++){
            uint32_t cur_res = sorted_res_vec[i][j - norm_dist];
            dp_mat[i][j] = cur_res;
        }
    }  // Half of the matrix filled.

    // Filling the rest of the half matrix.
    for(int i=0; i<dp_mat.size(); i++){
        for(int j=i; j<dp_mat[0].size(); j++){
            dp_mat[j][i] = dp_mat[i][j];
        }
    }
    return dp_mat;
}


void csv_writer::write_matrix_into_csv(string out_file){
    std::ofstream csv;
    csv.open (out_file);
    for(int i=0; i<dp_mat.size(); i++){
        for(int j=0; j<dp_mat[0].size(); j++){
            csv << dp_mat[i][j];
            if (j != dp_mat[0].size() - 1)
            {
                csv << ",";  // End of col.
            }
        }
        if(i != dp_mat.size() - 1)
        {
            csv << "\n";  // End of row.
        }
    }
    csv.close();
}

/* 
int main(){
    int arr_len = 27;
    uint32_t *res_arr = new uint32_t[arr_len];
    for(int i=0; i<arr_len; i++){
        res_arr[i] = 100;
    }
    vector<int> row_nums = {3, 3};

    csv_writer *csv_to_write = new csv_writer(res_arr, arr_len, row_nums);

    vector<vector<uint32_t>> dp_mat = csv_to_write->dp_mat;

    for(int i=0; i<dp_mat.size(); i++){
        for(int j=0; j<dp_mat[0].size(); j++){
            cout<<dp_mat[i][j]<<", ";
        }
        cout<<endl;
    }
}
*/