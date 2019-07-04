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
import collections


def count_elements_in_list(list):
    """
    Count the frequency of every elements in list.
    :param list: target list.
    :return: a counter object containing the targeted frequencies.
    """
    counter = collections.Counter(list)
    return counter


if __name__ == '__main__':
    # Test

    # Initialization
    dir_path = "/home/chen/Git_repositories/pprbf/src/data/"
    key = "test_labels"

    # Run code
    labels = get_labels(dir_path, key)
    label_distribution = count_elements_in_list(labels)
    print(label_distribution)
    print(type(label_distribution))
