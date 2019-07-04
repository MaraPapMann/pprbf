"""
@Author:
    Huajie Chen
@Aim:
    Use cross validation experiment to find the best parameters,
    namely "sigma", "C", "class_weight".
@Input:
    1.  Linear dot product matrix(-> rbf kernel matrix);
    2.  Data label;
    3.  "sigma";
    4.  "C";
    5.  "class_weight".
@Step:
    1.  Concatenate labels (Alice & Bob);
    2.  Splice the data and labels accordingly;
    3.  Load the cv_train/test data and labels into the SVM model using different parameters in rounds;
    4.  Use AUC or F1-score to estimate the performance.
@Output:
    The set of parameters with the highest performance.
"""

from os import listdir
from os.path import isfile, join
from linear_to_rbf_matrix import linear_to_rbf_matrix
from sklearn.svm import SVC
from sklearn.metrics import f1_score
import numpy as np

"""
Pt1.    Concatenate labels.
"""


def get_specific_files_in_dir(dir, key):
    """
    Get files' absolute paths with key words in it into a list.
    :param dir: path to directory;
    :param key: key word;
    :return: label_files: list of strings.
    """
    label_files = []
    files = [f for f in listdir(dir) if isfile(join(dir, f))]
    for file in files:
        if key in file:
            label_files.append(dir + file)  # Absolute path
    label_files.sort()
    return label_files


def concatenate_labels(label_files):
    """
    concatenate labels in files into a list.
    :param label_files: absolute paths to label files;
    :return: labels: list of integers.
    """
    labels = []
    for label_file in label_files:
        lines = open(label_file, 'r').readlines()
        labels.extend(lines)
    for i in range(len(labels)):
        labels[i] = int(labels[i][0])
    return labels


def get_labels(dir, key):
    """
    Capsulation of pt1.
    :param dir: path to directory;
    :param key: key word;
    :return: labels: list of integers.
    """
    label_files = get_specific_files_in_dir(dir, key)
    labels = concatenate_labels(label_files)
    return labels


"""
Pt1.    End.
"""

"""
Pt2.    Splice data and labels accordingly.
"""


def get_section_lengths(dir, key):
    """
    Get the length of each section in the kernel matrix(from a to b in row)
    :param dir: path to directory;
    :param key: key word;
    :return: section_length: list of length of sections
    """
    section_lengths = []
    label_files = get_specific_files_in_dir(dir, key)
    for label_file in label_files:
        lines = open(label_file, 'r').readlines()
        section_lengths.append(len(lines))
    return section_lengths


def splice_list_into_sections(kernel_mat, section_lengths):
    """
    Splice the kernel matrix into sections according to section length.
    :param kernel_mat: rbf kernel matrix;
    :param section_lengths: list of length of sections;
    :return: spliced_kernel_matrix: 3D-list of spliced matrix.
    """
    kernel_mat_in_sections = []
    sp = 0
    for sect_len in section_lengths:
        ep = sp + sect_len
        cur_section = []
        for i in range(sp, ep):
            cur_section.append(kernel_mat[i])
        kernel_mat_in_sections.append(cur_section)
        sp = ep
    return kernel_mat_in_sections


def generate_cv_index(section_lengths, fold_num):
    """
    Generate cv indices for all sections in kernel matrix and label list.
    :param section_lengths: a list containing length of sections;
    :param fold_num: number of folds;
    :return: cv_idx: cv indices: cv_idx / sections / folds / indices
    """
    cv_idx = []
    sp = 0
    for section_len in section_lengths:
        ep = sp + section_len
        fold_len = int(section_len / fold_num)
        fold_sp = sp
        cv_idx_this_section = []
        for i in range(fold_num):
            fold_ep = fold_sp + fold_len
            fold_sp_ep = [fold_sp, fold_ep]
            cv_idx_this_section.append(fold_sp_ep)
            fold_sp = fold_ep
        cv_idx.append(cv_idx_this_section)
        sp = ep
    return cv_idx


def construct_one_row_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat, cur_row_idx):
    """
    Construct only one row train or test data for cv experiment.
    :param test_fold_idx: index indicate the test fold;
    :param cv_idx_list: a list containing cv indices of folds in each section;
    :param kernel_mat: rbf kernel matrix;
    :param cur_row_idx: index indicating current row;
    :return: one row constructed data.
    """
    cur_row = kernel_mat[cur_row_idx]
    one_row = []
    for section in cv_idx_list:
        for i in range(len(section)):
            if i != test_fold_idx:
                cur_fold = section[i]
                sp_cur_fold = cur_fold[0]
                ep_cur_fold = cur_fold[1]
                for j in range(sp_cur_fold, ep_cur_fold):
                    one_row.append(cur_row[j])
    return one_row


def construct_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat, train_or_test):
    """
    Construct cv train or test data in one round(fold).
    :param test_fold_idx:
    :param cv_idx_list:
    :param kernel_mat:
    :param train_or_test:
    :return: cv train or test data matrix in one round(fold)
    """
    if train_or_test == "train":
        cv_train_data = []
        for section in cv_idx_list:
            for i in range(len(section)):
                if i != test_fold_idx:
                    cur_fold = section[i]
                    sp_cur_fold = cur_fold[0]
                    ep_cur_fold = cur_fold[1]
                    for j in range(sp_cur_fold, ep_cur_fold):
                        cur_row_idx = j
                        one_row = construct_one_row_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat,
                                                                          cur_row_idx)
                        cv_train_data.append(one_row)
        return cv_train_data
    elif train_or_test == "test":
        cv_test_data = []
        for section in cv_idx_list:
            for i in range(len(section)):
                if i == test_fold_idx:
                    cur_fold = section[i]
                    sp_cur_fold = cur_fold[0]
                    ep_cur_fold = cur_fold[1]
                    for j in range(sp_cur_fold, ep_cur_fold):
                        cur_row_idx = j
                        one_row = construct_one_row_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat,
                                                                          cur_row_idx)
                        cv_test_data.append(one_row)
        return cv_test_data
    else:
        raise Exception("train_or_test must be one of train and test.")


def construct_cv_train_or_test_labels(test_fold_idx, cv_idx_list, labels, train_or_test):
    """
    Construct cv train or test labels in one round(fold)
    :param test_fold_idx:
    :param cv_idx_list:
    :param labels:
    :param train_or_test:
    :return: cv train or test labels in one round(fold)
    """
    if train_or_test == "train":
        cv_train_label = []
        for section in cv_idx_list:
            for i in range(len(section)):
                if i != test_fold_idx:
                    cur_fold = section[i]
                    sp_cur_fold = cur_fold[0]
                    ep_cur_fold = cur_fold[1]
                    for j in range(sp_cur_fold, ep_cur_fold):
                        cv_train_label.append(labels[j])
        return cv_train_label
    elif train_or_test == "test":
        cv_test_label = []
        for section in cv_idx_list:
            for i in range(len(section)):
                if i == test_fold_idx:
                    cur_fold = section[i]
                    sp_cur_fold = cur_fold[0]
                    ep_cur_fold = cur_fold[1]
                    for j in range(sp_cur_fold, ep_cur_fold):
                        cv_test_label.append(labels[j])
        return cv_test_label
    else:
        raise Exception("train_or_test must be one of train and test.")


"""
Pt2.    End.
"""

"""
Pt3.    Load the cv_train/test data and labels into the SVM model using different parameters in rounds.
        Output the y in prediction for next step. 
"""


def cv_svm(cv_train_data, cv_train_labels, cv_test_data, class_weight, C):
    """
    Use "sklearn" svm to fit the cv train data and label;
    Afterwards apply it to the cv test data to get the prediction results.
    :param cv_train_data: cross validation train data;
    :param cv_train_labels: cross validation train labels;
    :param cv_test_data: cross validation test data;
    :return: pred_labels: prediction result in this fold.
    """
    clf = SVC(kernel="precomputed", class_weight=class_weight, C=C)
    clf.fit(cv_train_data, cv_train_labels)
    pred_labels = clf.predict(cv_test_data)
    return pred_labels


"""
Pt3.    End.
"""

"""
Pt4.    Use AUC or F1-score to estimate the performance.
"""


def estimation_f1_score(cv_pred_labels, cv_test_labels):
    return f1_score(cv_test_labels, cv_pred_labels, average="micro")


"""
Pt4.    End.
"""

"""
Final Capsulation.
"""


def cross_validation(dir_path, key, dp_mat_path, fold_num, C_lst, sigma_lst, class_weight_lst):
    labels = get_labels(dir_path, key)
    section_lengths = get_section_lengths(dir_path, key)
    cv_idx_list = generate_cv_index(section_lengths, fold_num)
    param_lst = []
    avg_f1_score_lst = []
    for sigma in sigma_lst:
        kernel_mat = linear_to_rbf_matrix(dp_mat_path, sigma)
        for C in C_lst:
            for class_weight in class_weight_lst:
                cur_param = [sigma, C, class_weight]
                avg_f1_score_under_this_param = []
                for test_fold_idx in range(fold_num):
                    cv_train_data = construct_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat, "train")
                    cv_test_data = construct_cv_train_or_test_data(test_fold_idx, cv_idx_list, kernel_mat, "test")
                    cv_train_labels = construct_cv_train_or_test_labels(test_fold_idx, cv_idx_list, labels, "train")
                    cv_test_labels = construct_cv_train_or_test_labels(test_fold_idx, cv_idx_list, labels, "test")
                    cv_pred_labels = cv_svm(cv_train_data, cv_train_labels, cv_test_data, class_weight, C)
                    cv_f1_score = estimation_f1_score(cv_pred_labels, cv_test_labels)
                    avg_f1_score_under_this_param.append(cv_f1_score)
                avg_f1_score_under_this_param = np.average(avg_f1_score_under_this_param)
                avg_f1_score_lst.append(avg_f1_score_under_this_param)
                param_lst.append(cur_param)
    max_f1_score_index = np.argmax(avg_f1_score_lst)
    best_param = param_lst[max_f1_score_index]
    cv_report = "The best parameters in this context are sigma = {:}, C = {:}, class_weight = {:} " \
                 "with the corresponding F1-score {:}.".format(best_param[0], best_param[1], best_param[2],
                                                        avg_f1_score_lst[max_f1_score_index])
    print("Average F1-score list:")
    print(avg_f1_score_lst)
    print(cv_report)
    file = open("./cv_report", "w")
    file.write(cv_report)
    file.close()


"""
Final Capsulation End.
"""

if __name__ == '__main__':
    # Test

    # Initialization
    dir_path = "/home/chen/Git_repositories/pprbf/src/data/"
    key = "test_labels"
    dp_mat_path = "/home/chen/Git_repositories/pprbf/src/rbf_kernel_svm/data/dp_mat.csv"
    fold_num = 5
    C_lst = [0.001, 0.01, 0.1, 1, 10, 100, 1000]
    sigma_lst = [0.125, 0.25, 0.5, 1, 2, 4, 8]
    class_weight_lst = [
        {0: 1, 1: 1},
        {0: 1, 1: 4},
        {0: 1, 1: 5},
        {0: 1, 1: 6},
        {0: 1, 1: 10}]

    # Run code
    cross_validation(dir_path, key, dp_mat_path, fold_num, C_lst, sigma_lst, class_weight_lst)
