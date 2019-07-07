"""
@Author:
    Huajie Chen
@Aim:
    To validate the result from the original code.
@Input:
    Original data and labels
@Step:
    1.  Calculate the dot product matrix and write it as a csv file;
    2.  Compute the rbf kernel matrix;
    3.  Run cross validation experiment;
    4.  Run the Support Vector Machine classifier.
@Output:
    1.  Cross validation report;
    2.  Final classifier F1 score.
"""

from os import listdir
from os.path import isfile, join
import pandas as pd
import timeit
import numpy as np
from cross_validation import cross_validation
from rbf_kernel_svm import *

"""
Pt 1.   Calculate the dot product matrix and write it as a csv file.
"""


def get_files_in_dir(dir_path):
    """
    Get all files' absolute path in given directory into a list
    :param dir_path: path to the target directory;
    :return: files: list of files.
    """
    files = [f for f in listdir(dir_path) if isfile(join(dir_path, f))]
    files.sort()  # sort the list lexicographically.
    for i in range(len(files)):
        files[i] = dir_path + files[i]
    return files


def parse_one_file_as_list(file_path):
    """
    Parse one files as a list object.
    :param file_path: path to the file;
    :return: a list object containing needed data; List / Vector / Cell.
    """
    lst_to_return = []
    file = pd.read_csv(file_path, header=None)
    row_num = file.shape[0]
    col_num = file.shape[1]
    for i in range(row_num):
        cur_row = []
        for j in range(col_num):
            cur_row.append(file.iloc[i, j])
        lst_to_return.append(cur_row)
    return lst_to_return


def parse_files_as_list(dir_path):
    """youpikuaifang
    Parse all files in given directory as a list object.
    :param dir_path: path to the target directory;
    :return: a list object containing needed data; List / File / Vector / Cell.
    """
    lst_to_return = []
    files = get_files_in_dir(dir_path)
    for file in files:
        cur_file_lst = parse_one_file_as_list(file)
        lst_to_return.append(cur_file_lst)
    return lst_to_return


def calc_dp_between_2_files(file_a, file_b):
    """
    Calculate dot product between 2 files as a 2D list object.
    :param file_a: data from file a: a 2D list; Vector / Cell;
    :param file_b: data from file b: a 2D list; Vector / Cell;
    :return: dot product vector: a 2D list; Row / Column; each cell is a dot product from 2 vectors.
    """
    lst_to_return = []
    for cur_vec_a in file_a:
        cur_dp_res = []
        for cur_vec_b in file_b:
            cur_dp = np.dot(cur_vec_a, cur_vec_b)
            cur_dp_res.append(cur_dp)
        lst_to_return.append(cur_dp_res)
    return lst_to_return


def calc_dp_between_files(files):
    """
    Calculate dot products between files accordingly.
    :param files: Parsed files in list object form;
    :return: dot products between files; List / Between files / Vector / Cell.
    """
    dp_between_files = []
    for i in range(len(files)):
        file_a = files[i]
        for j in range(i, len(files)):
            file_b = files[j]
            dp_between_files.append(calc_dp_between_2_files(file_a, file_b))
    return dp_between_files


def get_section_len(files):
    """
    Get the length of one section, namely number of dot product section from file_a and another file_b.
    :param files: parsed files in the form of list object;
    :return: length of sections; list; List / Section Length.
    """
    section_len = []
    for i in range(len(files)):
        section_len.append(len(files) - i)
    return section_len


def get_subsection_len(files):
    """
    Get the length of one subsection, namely nubmer of dot product subsection from vector_a and another vector_b.
    :param files: parsed files in the form of list object;
    :return: length of sections; list; List / Section Length.
    """
    subsection_len = []
    for i in range(len(files)):
        for j in range(i, len(files)):
            subsection_len.append(len(files[i]))
    return subsection_len


def sort_vec(dp_between_files, section_len):
    """
    Sort the dot product row by row, column by column.
    :param dp_between_files: dot product between files;
    :param section_len: length of sections;
    :return: sorted vector.
    """
    section_sp = 0
    sorted_vec = []
    for i in range(len(section_len)):  # In one section. Every single dot product between files shares the same length
        # (for the same number of vector in file_a).
        cur_sect_len = section_len[i]
        section_ep = section_sp + cur_sect_len
        sorted_vec_in_sect = []
        for j in range(len(dp_between_files[section_sp])):
            temp_sorted_vec = []
            for k in range(section_sp, section_ep):
                temp_sorted_vec.extend(dp_between_files[k][j])
            sorted_vec_in_sect.append(temp_sorted_vec)
        sorted_vec.append(sorted_vec_in_sect)
        section_sp = section_ep
    return sorted_vec


def get_dp_mat(files, dp_between_files, section_len):
    """
    Calculate the dot product matrix.
    :param files:
    :param dp_between_files:
    :param section_len:
    :return: The final dot product matrix.
    """
    # Get total number of the vectors and the length of file.
    vec_num = 0
    file_len = []
    for file in files:
        file_len.append(len(file))
        vec_num = vec_num + len(file)

    # Initialize the matrix.
    dp_mat = np.zeros((vec_num, vec_num))

    # Sort the vectors.
    sorted_vec = sort_vec(dp_between_files, section_len)

    # Fill the matrix.
    sp = 0
    for i in range(len(file_len)):
        cur_file_len = file_len[i]
        cur_section = sorted_vec[i]
        ep = sp + cur_file_len
        for r_idx in range(len(cur_section)):
            cur_row = cur_section[r_idx]
            for c_idx in range(len(cur_row)):
                cur_cell = cur_row[c_idx]
                dp_mat[r_idx + sp][c_idx + sp] = cur_cell
        sp = ep

    # Write the matrix symmetrically.
    for i in range(dp_mat.shape[0]):
        for j in range(dp_mat.shape[1]):
            dp_mat[j][i] = dp_mat[i][j]

    return dp_mat


def write_dp_mat_into_csv(file_path, dp_mat):
    """
    Write the dot product matrix into csv file.
    :param file_path:
    :param dp_mat:
    :return:
    """
    file = open(file_path, "w")
    for i in range(dp_mat.shape[0]):
        for j in range(dp_mat.shape[1]):
            file.write(str(dp_mat[i][j]))
            if i != dp_mat.shape[0] - 1:
                if j == dp_mat.shape[1] - 1:
                    file.write("\n")
                else:
                    file.write(",")
            else:
                if j != dp_mat.shape[1] - 1:
                    file.write(",")
    return


def from_encoded_seq_to_dp_mat(dir_path, file_name):
    """
    Final capsulation of Pt 1.
    :param dir_path:
    :param file_name:
    :return:
    """
    files = parse_files_as_list(dir_path)
    dp_between_files = calc_dp_between_files(files)
    section_len = get_section_len(files)
    dp_mat = get_dp_mat(files, dp_between_files, section_len)
    write_dp_mat_into_csv(file_name, dp_mat)


"""
Pt 1.   End.
"""

"""
Pt 2.   Compute the rbf kernel matrix.
"""

"""
Pt 2.   End.
"""

"""
Pt 3.   Run cross validation experiment.
"""

"""
Pt 3.   End.
"""

"""
Pt 4.   Run Support Vector Machine Classifier.
"""

"""
Pt 4.   End.
"""

if __name__ == '__main__':
    # Test
    st = timeit.default_timer()

    # Initialization
    dir_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/train/"
    file_name = dir_path + "dp_mat.csv"

    # Run code
    """
    Calculate dot product matrix
    ---
    from_encoded_seq_to_dp_mat(dir_path, file_name)
    """

    """
    Cross Validation
    ---
    cv_test_labels_dir_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/train/label/"
    key = "labels"
    dp_mat_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/train/dp_mat.csv"
    fold_num = 5
    C_lst = [0.001, 0.01, 0.1, 1, 10, 100, 1000]
    sigma_lst = [0.125, 0.25, 0.5, 1, 2, 4, 8]
    class_weight_lst = [
        {0: 1, 1: 1},
        {0: 1, 1: 4},
        {0: 1, 1: 5},
        {0: 1, 1: 6},
        {0: 1, 1: 10}]
    cross_validation(cv_test_labels_dir_path, key, dp_mat_path, fold_num, C_lst, sigma_lst, class_weight_lst)
    """

    # Initialization
    train_dp_mat_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/train/dp_mat.csv"
    test_dp_mat_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/test/dp_mat.csv"
    train_labels_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/train/label/"
    train_labels_key = "labels"
    test_labels_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/test/label/"
    test_labels_key = "test_labels"
    sigma = 8
    C = 10
    class_weight = {0: 1, 1: 1}

    # Get rbf kernel matrix
    X_train = get_data(train_dp_mat_path, sigma)
    X_test = get_data(test_dp_mat_path, sigma)
    Y_train = get_labels(train_labels_path, train_labels_key)
    Y_test = get_labels(test_labels_path, test_labels_key)
    Y_pred = get_prediction(X_train, Y_train, X_test, C, class_weight)
    F1_score = estimation_f1_score(Y_pred, Y_test)
    print("The F1-Score of the given svm classifier is {:}".format(F1_score))
    ed = timeit.default_timer()
    print("Time: {:} seconds".format(ed - st))
