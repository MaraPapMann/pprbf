"""
@Author:
    Huajie Chen
@Aim:
    To get the optimal SVM model in this context.
@Input:
    1.  Linear dot product matrix;
    2.  Sigma;
    3.  C;
    4.  Class_weight.
@Step:
    1.  Use sigma to compute rbf kernel matrix;
    2.  CV experiments for optimizing the best "sigma", "C" and "class_weight"(CCR5:1, not-CCR5:4) parameter;
    3.  Train SVM model using "C" and "class_weight"(weight for penalty) on the training fold and test it
        on test fold;
    4.  Use F1-score or AUC for the final performance estimation.
@Output:
    An optimal SVM model | Corresponding parameters.
"""

from linear_to_rbf_matrix import linear_to_rbf_matrix
from cross_validation import get_labels
from cross_validation import estimation_f1_score
from sklearn.svm import SVC
import pandas as pd
import timeit


def get_data(dp_mat_path, sigma):
    X = linear_to_rbf_matrix(dp_mat_path, sigma)
    return X


def get_prediction(X_train, Y_train, X_test, C, class_weight):
    clf = SVC(C=C, class_weight=class_weight, kernel="precomputed")
    clf.fit(X_train, Y_train)
    Y_pred = clf.predict(X_test)
    return Y_pred


def get_train_test_data(merged_dp_mat_path, train_dp_mat_path, sigma):
    org_kernel_matrix = get_data(merged_dp_mat_path, sigma)
    X_pre_train = pd.read_csv(train_dp_mat_path, header=None)
    length = X_pre_train.shape[0]
    X_train = org_kernel_matrix[:length, :length]
    X_test = org_kernel_matrix[length:, :length]
    return X_train, X_test


if __name__ == '__main__':
    # Test


    # Initialization
    sigma = 3
    C = 0.5
    class_weight = {0: 1, 1: 5}
    train_dp_mat_path = "new_cross_validation/reshuffled_data/reshuffled_train_data.csv"
    test_dp_mat_path = "new_cross_validation/reshuffled_data/reshuffled_test_data.csv"
    train_labels_path = "new_cross_validation/reshuffled_data/"
    train_labels_key = "train_label"
    test_labels_path = "new_cross_validation/reshuffled_data/"
    test_labels_key = "test_label"
    merged_dp_mat_path = "new_cross_validation/reshuffled_data/reshuffled_dp_mat.csv"

    # Get rbf kernel matrix
    # X_train = get_data(train_dp_mat_path, sigma)
    X_train, X_test = get_train_test_data(merged_dp_mat_path, train_dp_mat_path, sigma)

    start = timeit.default_timer()
    Y_train = get_labels(train_labels_path, train_labels_key)
    Y_test = get_labels(test_labels_path, test_labels_key)
    Y_pred = get_prediction(X_train, Y_train, X_test, C, class_weight)

    F1_score = estimation_f1_score(Y_pred, Y_test)
    print("The F1-Score of the given svm classifier is {:}".format(F1_score))

    end = timeit.default_timer()
    print("Time: {:}".format(end - start))
