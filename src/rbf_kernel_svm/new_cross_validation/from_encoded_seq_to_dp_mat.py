import numpy as np
import pandas as pd
import timeit

if __name__ == '__main__':
    start = timeit.default_timer()

    # Parse File
    encoded_seq = pd.read_csv("/home/mara-pap-mann/github/pprbf/src/rbf_kernel_svm/new_cross_validation/reshuffled_data/reshuffled_encoded_seq.csv", header=None)

    # Calculate dot product matrix
    dp_mat = []
    for i in range(encoded_seq.shape[0]):
        cur_row = []
        for j in range(encoded_seq.shape[0]):
            cur_row.append(np.dot(encoded_seq.iloc[i, :], encoded_seq.iloc[j, :]))
        dp_mat.append(cur_row)
        print("{:} of {:} is complete.".format(i, encoded_seq.shape[0]))

    print("Dot products calculation complete!")

    # Write it into files
    file = open("reshuffled_dp_mat.csv", "w")
    for i in range(len(dp_mat)):
        for j in range(len(dp_mat[0])):
            file.write(str(dp_mat[i][j]))
            if j != len(dp_mat[0]) - 1:
                file.write(",")
            else:
                if i != len(dp_mat) - 1:
                    file.write("\n")
    file.close()

    # Write train data
    num_train = 612
    file = open("reshuffled_train_data.csv", "w")
    for i in range(num_train):
        for j in range(num_train):
            file.write(str(dp_mat[i][j]))
            if j != num_train - 1:
                file.write(",")
            else:
                if i != num_train - 1:
                    file.write("\n")
    file.close()

    # Write test data
    num_test = 154
    file = open("reshuffled_test_data.csv", "w")
    for i in range(num_train, num_train + num_test):
        for j in range(num_train):
            file.write(str(dp_mat[i][j]))
            if j != num_train - 1:
                file.write(",")
            else:
                if i != num_train + num_test - 1:
                    file.write("\n")
    file.close()
    end = timeit.default_timer()
    print("Time: {:} seconds".format(end - start))
