import matplotlib.pyplot as plt

if __name__ == '__main__':
    x = ["10e4", "10e5", "10e6", "10e7", "10e8"]  # X axis label
    ac_times = [79.196, 494.313, 4320.19, 44092.7, None]  # Arithmetic circuit's time
    bc_times = [18.93, 91.547, 1022.67, 8243.21, 73914.9]  # Boolean circuit's time
    plt.plot(x, ac_times, 's-', color='red', label="Arithmetic Circuit")
    plt.plot(x, bc_times, 'o-', color='blue', label="Boolean Circuit")
    plt.xlabel("Array Size: 1")
    plt.ylabel("Circuit Time: ms")
    plt.legend(loc="best")
    plt.title("Time Cost of Circuits with Increasing Array Size(bit length = 1)")
    plt.show()
