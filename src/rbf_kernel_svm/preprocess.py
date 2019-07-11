"""
@Author:
    Huajie Chen
@Aim:
    Get to know the data property and conduct pre-process to data.
@Input:
    Original data and labels
@Step:
    1.  Parse the file and see its distribution;
    2.  Pre-process
@Output:
    ...
"""

from cross_validation import get_labels
from validation import from_encoded_seq_to_dp_mat
import collections
import pandas as pd


def count_elements_in_list(list):
    """
    Count the frequency of every elements in list.
    :param list: target list.
    :return: a counter object containing the targeted frequencies.
    """
    counter = collections.Counter(list)
    return counter


def get_train_test_data(merged_dp_mat_path, ratio, out_dir):
    dp_mat = pd.read_csv(merged_dp_mat_path, header=None)
    row_num = dp_mat.shape[0]
    col_num = dp_mat.shape[1]
    train_data = dp_mat.iloc[:int(row_num * ratio), :int(col_num * ratio)]
    test_data = dp_mat.iloc[int(row_num * ratio):, :int(col_num * ratio)]
    train_data.to_csv(out_dir + "train_data.csv", header=False, index=False)
    test_data.to_csv(out_dir + "test_data.csv", header=False, index=False)
    return


def get_train_test_labels(merged_labels_path, ratio, out_dir):
    labels = pd.read_csv(merged_labels_path, header=None)
    row_num = labels.shape[0]
    train_label = labels.iloc[:int(row_num * ratio)]
    test_label = labels.iloc[int(row_num * ratio):]
    train_label.to_csv(out_dir + "train_label.csv", header=False, index=False)
    test_label.to_csv(out_dir + "test_label.csv", header=False, index=False)
    return


def split_label(label_path, seg_num, out_dir):
    label = pd.read_csv(label_path, header=None)
    row_num = label.shape[0]
    seg_length = int(row_num / seg_num)
    for i in range(seg_num):
        cur_seg_label = label.iloc[i * seg_length:(i + 1) * seg_length]
        cur_seg_label.to_csv(out_dir + "split_label_{:}.csv".format(i), header=False, index=False)
    return


def concat_2_df(df1, df2):
    df = pd.concat([df1, df2], axis=0)
    print(df.shape)


if __name__ == '__main__':
    # Test

    # Initialization
    dir_path = "data/"
    key = "test_labels"
    merged_dp_mat_path = "data/merged_data/merged_dp_mat.csv"
    merged_labels_path = "data/merged_label/merged_labels.txt"
    ratio = 0.8
    df1 = pd.read_csv("data/test/label/split_label_0.csv", header=None)
    df2 = pd.read_csv("data/test/label/split_label_1.csv", header=None)

    # Run code
    # labels = get_labels(dir_path, key)
    # label_distribution = count_elements_in_list(labels)
    # print(label_distribution)
    # print(type(label_distribution))
    # from_encoded_seq_to_dp_mat(dir_path, dir_path + "merged_dp_mat.csv")
    # get_train_test_data(merged_dp_mat_path, ratio, dir_path)
    # get_train_test_labels(merged_labels_path, ratio, dir_path)
    # split_label("data/test/label/test_label.csv", 2, "data/test/label/")
    # split_label("data/train/label/train_label.csv", 2, "data/train/label/")
    concat_2_df(df1, df2)
