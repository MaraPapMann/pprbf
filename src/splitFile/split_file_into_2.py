import numpy as np
import pandas as pd
import os
import sys
import getopt


def get_all_files_in_dir(dir):
    """
    Get all files in given directory as list.
    :param dir: path to the target directory.
    :return: files: list; a list containing all files' absolute paths.
    """
    files = []
    for dirpath, _, filenames in os.walk(dir):
        for f in filenames:
            files.append(os.path.abspath(os.path.join(dirpath, f)))
    return files


# I: Path of a file(str), bit length(int)
# O: Two encrypted split matrix(list)
# Interp. Encrypt the given file, split the file into two files.
def split_file(in_file, bit_length):
    """
    :param in_file:
    :param bit_length:
    :return:
    """
    if bit_length not in [1, 8, 16, 32, 64]:
        raise ValueError('bit_length should be one of [1, 8, 16, 32, 64].')
    else:
        if bit_length != 1:
            try:
                in_file = pd.read_csv(in_file, header=None)
                lst_to_return_1 = []
                lst_to_return_2 = []
                shape = in_file.shape
                for i in range(shape[0]):
                    cur_vector_1 = []
                    cur_vector_2 = []
                    for j in range(shape[1]):
                        cur_val = in_file.iloc[i, j]
                        cur_random_val = np.random.randint(0, 2 ** bit_length)  # Upper bound need to + 1
                        cur_vector_1.append(cur_random_val)
                        cur_vector_2.append(abs(cur_val + 2 ** bit_length - cur_random_val))
                    lst_to_return_1.append(cur_vector_1)
                    lst_to_return_2.append(cur_vector_2)
                return lst_to_return_1, lst_to_return_2
            except ValueError:
                print('Please input a proper CSV file')
        else:  # bit_length = 1
            try:
                in_file = pd.read_csv(in_file, header=None)
                lst_to_return_1 = []
                lst_to_return_2 = []
                shape = in_file.shape
                for i in range(shape[0]):
                    cur_vector_1 = []
                    cur_vector_2 = []
                    for j in range(shape[1]):
                        cur_val = in_file.iloc[i, j]
                        cur_random_val = np.random.randint(0, 2 ** bit_length)  # Upper bound need to + 1
                        cur_vector_1.append(cur_random_val)
                        if cur_val == 0:
                            if cur_random_val == 0:
                                cur_vector_2.append(0)
                            else:
                                cur_vector_2.append(1)
                        else:
                            if cur_random_val == 1:
                                cur_vector_2.append(0)
                            else:
                                cur_vector_2.append(1)
                    lst_to_return_1.append(cur_vector_1)
                    lst_to_return_2.append(cur_vector_2)
                return lst_to_return_1, lst_to_return_2
            except ValueError:
                print('Please input a proper CSV file')


# I: Split file matrix(list), Output name(str)
# O:
# Interp. Write the split file into csv file.
def write_csv(in_lst, out_name):
    file = open(out_name, 'w')
    for i in range(len(in_lst)):
        cur_vec = in_lst[i]
        if i != len(in_lst) - 1:
            for j in range(len(in_lst[0])):
                cur_val = cur_vec[j]
                if j != len(in_lst[0]) - 1:
                    file.write(str(cur_val))
                    file.write(',')
                else:
                    file.write(str(cur_val))
                    file.write('\n')  # Last column
        else:  # Last row
            for j in range(len(in_lst[0])):
                cur_val = cur_vec[j]
                if j != len(in_lst[0]) - 1:
                    file.write(str(cur_val))
                    file.write(',')
                else:
                    file.write(str(cur_val))  # Very last one cell
    file.close()


# I: Command line input arguments(list)
# O: Target directory and bit length(tuple)
# Interp. Parsing the command line arguments and pass them to the upcoming functions.
def parse_command_line_arguments(argv):
    dir = ''
    bit_length = ''
    try:
        opts, args = getopt.getopt(argv, "hi:b:", ["indir=", "bitlength="])
    except getopt.GetoptError:
        print('test.py -i <inputDir> -b <bitLength>')
        sys.exit(2)
    for opt, arg in opts:
        if opt == '-h':
            print('test.py -i <inputDir> -b <bitLength>')
            sys.exit()
        elif opt in ("-i", "--indir"):
            dir = arg
        elif opt in ("-b", "--bitlength"):
            bit_length = arg
    print('Input directory is "' + dir + '"')
    print('Bit length is "' + bit_length + '"')
    return dir, bit_length


if __name__ == '__main__':
    target_dir, bit_length = parse_command_line_arguments(sys.argv[1:])
    files = get_all_files_in_dir(target_dir)
    #   print(files)    Tested
    for file in files:  # Map to all files
        lst_1, lst_2 = split_file(file, int(bit_length))
        write_csv(lst_1, file + "_cross_dp_split_1.csv")
        write_csv(lst_2, file + "_cross_dp_split_2.csv")
    #   in_file = pd.read_csv("./probe_1.csv", header=None) Tested
    #   print(input.shape)   Tested
    #   lst_1, lst_2 = split_file(in_file, 8)   Tested
    #   print(lst_1)    Tested
    #   print(lst_2)    Tested
    #   write_csv(lst_1, "probe_split_1")   Tested
    #   write_csv(lst_2, "probe_split_2")   Tested
