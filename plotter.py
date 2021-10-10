import matplotlib.pyplot as plt


def get_date(file_path):
    nb, gflops = [], []
    with open(file_path) as f:
        for l in f:
            if len(l) < 4:
                continue

            data = l.split(',')
            nb.append(int(data[0].split(':')[1]))

            gflops.append(float(data[1].split(':')[1][:-1]))

    return nb, gflops


def plot():
    nb1, gflops1 = get_date("NB-gflops-p1.txt")
    nb2, gflops2 = get_date("NB-gflops-p2.txt")
    nb3, gflops3 = get_date("NB-gflops-p3.txt")

    plt.plot(nb1, [0.5]*4, label="p0")
    plt.plot(nb1, gflops1, label="p1", marker='o')
    plt.plot(nb2, gflops2, label="p2", marker='o')
    plt.plot(nb3, gflops3, label="p3", marker='o')

    plt.xlabel("NB sizes")
    plt.ylabel("Performance (in GFLOPS)")
    plt.title("Micro-MMM benchmark")
    plt.legend()
    plt.show()

    n, gflops = get_date('program3-exec-time.txt')
    plt.plot(n, gflops, label='p3', marker='o')
    plt.xlabel("N")
    plt.ylabel("Performance (in GFLOPS)")
    plt.title("MMM benchmark - NB: 16")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    plot()

