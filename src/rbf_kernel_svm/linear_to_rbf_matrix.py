"""
@Author: Huajie Chen
@Aim: To calculate the rbf kernel matrix based on the linear kernel(dot product) matrix.
@Input: Linear kernel matrix(row from a to z, column from a to z)
@Step:
    1.  RBF Kernel Formula: K(x, y) = exp(||x - y||^2 / -2*sigma^2);
    2.  ||x - y||^2 = x*x - 2xy + y*y;
    3.  Sigma is a manual input parameter;
    4.  Compute the matrix row by row accordingly.
"""

import numpy as np
import pandas as pd


def rbf_kernel_formula(norm_xy, sigma):
    """
    Calculate the rbf kernel matrix(one cell)
    :param norm_xy: norm of (x-y)
    :param sigma: manual parameter
    :return: rbf kernel dot product(one cell)
    """
    rbf_kernel_dp = np.exp(norm_xy / (-2 * sigma ** 2))
    return rbf_kernel_dp


def get_norm_xy(xx, xy, yy):
    """
    Get norm of (x-y).
    :param xx: dot product of x and x;
    :param xy: dot product of x and y;
    :param yy: dot product of y and y;
    :return: norm of (x-y)
    """
    norm_xy = xx - 2 * xy + yy
    return norm_xy


def get_input_dp_mat(file_path):
    dp_mat = pd.read_csv(file_path, header=None)
    return dp_mat


def get_corresponding_index(cur_i, cur_j):
    """
    Get the corresponding index for xx, xy, yy for calculation.
    :param cur_i: current index i;
    :param cur_j: current index j;
    :return: corresponding_index: [xx_idx, xy,idx, yy_idx]
    """
    xx_idx = [cur_i, cur_i]
    xy_idx = [cur_i, cur_j]
    yy_idx = [cur_j, cur_j]
    corresponding_index = [xx_idx, xy_idx, yy_idx]
    return corresponding_index


def get_rbf_kernel_matrix(dp_mat, sigma):
    """
    To get the rbf_kernel_matrix
    :param dp_mat: linear dot product matrix calculated before;
    :return: rbf_kernel_matrix: np.matrix
    """
    dp_mat_rank = dp_mat.shape
    rbf_kernel_mat = np.zeros(dp_mat_rank)
    for i in range(dp_mat_rank[0]):
        for j in range(dp_mat_rank[1]):
            cur_cor_index = get_corresponding_index(i, j)
            cur_xx_idx = cur_cor_index[0]
            cur_xy_idx = cur_cor_index[1]
            cur_yy_idx = cur_cor_index[2]
            cur_xx = dp_mat.iloc[cur_xx_idx[0], cur_xx_idx[1]]
            cur_xy = dp_mat.iloc[cur_xy_idx[0], cur_xy_idx[1]]
            cur_yy = dp_mat.iloc[cur_yy_idx[0], cur_yy_idx[1]]
            cur_norm_xy = get_norm_xy(cur_xx, cur_xy, cur_yy)
            cur_rbf_kernel_dp = rbf_kernel_formula(cur_norm_xy, sigma)
            rbf_kernel_mat[i, j] = cur_rbf_kernel_dp
    return rbf_kernel_mat


if __name__ == '__main__':
    dp_mat = get_input_dp_mat("./data/dp_mat.csv")
    sigma = 1
    rbf_kernel_mat = get_rbf_kernel_matrix(dp_mat, sigma)
    print(rbf_kernel_mat)
