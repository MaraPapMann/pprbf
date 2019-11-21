import timeit
import pandas as pd
import random as rd

if __name__ == '__main__':
    start = timeit.default_timer()

    # 1. Parse merged data and labels into lists.

    merged_data = pd.read_csv("merged_data/encoded_seq.csv", header=None)
    merged_label = pd.read_csv("merged_data/merged_label.csv", header=None)

    merged_data_lst = []
    merged_label_lst = []

    for i in range(merged_data.shape[0]):
        cur_row = []
        for j in range(merged_data.shape[1]):
            cur_row.append(merged_data.iloc[i, j])
        merged_data_lst.append(cur_row)

    for i in range(merged_label.shape[0]):
        merged_label_lst.append(merged_label.iloc[i, 0])

    print("Data and labels are parsed into lists.")

    # 2. Get the proportion of "1" and "0" of the label.

    num_label_0 = 0
    num_label_1 = 0
    idx_label_0 = []
    idx_label_1 = []

    for i in range(len(merged_label_lst)):
        if merged_label_lst[i] == 0:
            num_label_0 = num_label_0 + 1
            idx_label_0.append(i)
        else:
            num_label_1 = num_label_1 + 1
            idx_label_1.append(i)

    print("Number of label 0 : 1 = {:} : {:}".format(num_label_0, num_label_1))
    print("Indices are obtained.")

    # 3. Split the data according to the proportion.
    num_train_data = 612
    num_test_data = 154
    ratio_zero = num_label_0 / (num_label_0 + num_label_1)

    train_data = []
    train_label = []
    test_data = []
    test_label = []

    num_zero_in_test_data = int(num_test_data * ratio_zero)
    num_one_in_test_data = num_test_data - num_zero_in_test_data

    test_data_zero_idx = rd.sample(idx_label_0, num_zero_in_test_data)
    test_data_one_idx = rd.sample(idx_label_1, num_one_in_test_data)
    train_data_zero_idx = idx_label_0
    for idx in test_data_zero_idx:
        train_data_zero_idx.remove(idx)
    train_data_one_idx = idx_label_1
    for idx in test_data_one_idx:
        train_data_one_idx.remove(idx)

    print(len(test_data_zero_idx))
    print(len(test_data_one_idx))
    print(len(train_data_zero_idx))
    print(len(train_data_one_idx))

    for idx in test_data_zero_idx:
        test_data.append(merged_data_lst[idx])
        test_label.append(0)

    for idx in test_data_one_idx:
        test_data.append(merged_data_lst[idx])
        test_label.append(1)

    for idx in train_data_zero_idx:
        train_data.append(merged_data_lst[idx])
        train_label.append(0)

    for idx in train_data_one_idx:
        train_data.append(merged_data_lst[idx])
        train_label.append(1)

    test_shuffle = list(zip(test_data, test_label))
    rd.shuffle(test_shuffle)
    test_data, test_label = zip(*test_shuffle)

    train_shuffle = list(zip(train_data, train_label))
    rd.shuffle(train_shuffle)
    train_data, train_label = zip(*train_shuffle)

    print(len(test_data))
    print(len(test_label))
    print(test_label)
    print(len(train_data))
    print(len(train_label))
    print(train_label)

    # 4. Write the data into csv files.

    file = open("reshuffled_encoded_seq.csv", "w")
    for i in range(len(train_data)):
        for j in range(len(train_data[0])):
            file.write(str(train_data[i][j]))
            if j != len(train_data[0]) - 1:
                file.write(",")
            else:
                file.write("\n")
    for i in range(len(test_data)):
        for j in range(len(test_data[0])):
            file.write(str(test_data[i][j]))
            if j != len(test_data[0]) - 1:
                file.write(",")
            else:
                if i != len(test_data) - 1:
                    file.write("\n")
    file.close()

    file = open("reshuffled_train_label.csv", "w")
    for i in range(len(train_label)):
        file.write(str(train_label[i]))
        if i != len(train_label):
            file.write("\n")
    file.close()

    file = open("reshuffled_test_label.csv", "w")
    for i in range(len(test_label)):
        file.write(str(test_label[i]))
        if i != len(test_label):
            file.write("\n")
    file.close()

    end = timeit.default_timer()
    print("Time: {:} seconds".format(end - start))
