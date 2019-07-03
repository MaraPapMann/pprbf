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

if __name__ == '__main__':
    # Test

    # Initialization
    dp_mat_path = "./data/dp_mat.csv"
    sigma = 1

    # Get rbf kernel matrix
    rbf_kernel_mat = linear_to_rbf_matrix(dp_mat_path, sigma)
    print(rbf_kernel_mat)