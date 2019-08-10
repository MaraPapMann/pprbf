/**
 *  @Author:
 *      Huajie Chen
 *  @Aim:
 *      Transform the result array to a sorted matrix and write it to a csv file.
 *  @Input:
 *      1.  res_arr: result array;
 *      2.  array_length: length of the result array;
 *      3.  row_nums: vector containing row numbers of each file.
 *  @Output:
 *      1. dp_mat: dot product matrix;
 *      2. write the dot product matrix into csv file.
 */
#ifndef CSV_WRITER_
#define CSV_WRITER_


#include <iostream>
#include <ENCRYPTO_utils/crypto/crypto.h>
#include <ENCRYPTO_utils/parse_options.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
using namespace std;


class csv_writer
{
private:
    vector<uint32_t> res_vec;
    vector<int> row_nums;

    /**
     * Get length of all sections of dot product results in a vector(1 file vs. rest of the file).
     * @param: row_nums: vector<int>; vector containing row numbers of files in target directory.
     * return: vec_section: vector<int>; 
     */
    vector<int> get_section_vec(vector<int> row_nums);

    vector<int> section_vec = csv_writer::get_section_vec(row_nums);

    /**
     * Get length of subsection of dot product results in a vector(1 file vs. each of rest of the file).
     * @param: row_nums: vector<int>; vector containing row numbers of files in target directory.
     * return: vec_subsection: vector<int>
     */
    vector<vector<int>> get_subsection_vec(vector<int> row_nums);

    vector<vector<int>> subsection_vec = csv_writer::get_subsection_vec(row_nums);

    /**
     * Splice result vector into sections according to the section vector
     * @param: res_vec: vector<uint32_t>; result vector.
     * @param: section_vec: vector<int>; vector containing the length of each section.
     * return: res_vec_in_sections: vector<vector<uint32_t>>; 2D vector containing results spliced into sections.
     */
    vector<vector<uint32_t>> splice_res_vec_into_sections(vector<uint32_t> res_vec, vector<int> section_vec);
    
    vector<vector<uint32_t>> res_vec_in_sections = splice_res_vec_into_sections(res_vec, section_vec);

    /**
     * Splice result in sections into subsections in vector.
     * @param: res_vec_in_sections: vector<vector<uint32_t>>; result vector spliced into sections.
     * @param: subsection_vec: vector<vector<int>>; 2D vector containing length of each subsection in each section.
     * return: res_vec_in_subsections: vector<vector<vector<uint32_t>>>; 3D vector containing results spliced into subsections.
     */
    vector<vector<vector<uint32_t>>> splice_res_vec_in_sections_into_subsections(vector<vector<uint32_t>> res_vec_in_sections,
                                                                             vector<vector<int>> subsection_vec);
                                                                             
    vector<vector<vector<uint32_t>>> res_vec_in_subsections = splice_res_vec_in_sections_into_subsections(res_vec_in_sections, subsection_vec);

    /**
     * Sort the result vector according to the original file order(from file a to z)
     * @param: row_nums: vector<int>; 1D vector containing row numbers.
     * @param: res_vec_in_subsections: vector<vector<vector<uint32_t>>>; 3D vector containing results spliced into subsections.
     * return: sorted_res_vec: vector<vector<uint32_t>>; 2D vector containing sorted results.
     */
    vector<vector<uint32_t>> sorting_res_vec(vector<int> row_nums, vector<vector<vector<uint32_t>>> res_vec_in_subsections);

    vector<vector<uint32_t>> sorted_res_vec = sorting_res_vec(row_nums, res_vec_in_subsections);

    /**
     * Get the dot product matrix.
     * @param: sorted_res_vec: vector<vector<uint32_t>>; Sorted result vector.
     * return: dp_mat: vector<vector<uint32_t>>; dot product matrix, each cell is a result from any 2 vectors in order.
     */
    vector<vector<uint32_t>> get_dp_matrix(vector<vector<uint32_t>> sorted_res_vec);

public:
    // Transform the result array to a vector.
    vector<uint32_t> from_array_to_vector(uint32_t *res_array, int array_length);

    // Initiator.
    csv_writer(uint32_t *res_arr, int array_length, vector<int> row_nums):
    res_vec(csv_writer::from_array_to_vector(res_arr, array_length)),
    row_nums(row_nums)
    {};

    // The dot product matrix
    vector<vector<uint32_t>> dp_mat = csv_writer::get_dp_matrix(sorted_res_vec);

    /**
     * Write the product matrix into csv file locally.
     * @param: input_mat: vector<vector<uint32_t>>; 2D vector containing ordered dot product matrix.
     */
    void write_matrix_into_csv(string out_file);
};

#endif