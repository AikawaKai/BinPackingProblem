import sys
import os
import csv
import matplotlib.pyplot as plt


if __name__ == '__main__':

    path = sys.argv[1]
    files = os.listdir(path)
    files = [path+"/"+file_ for file_ in files if file_.endswith("SQD.csv")]
    opened_files = []
    for file_ in files:
        with open(file_, "r") as f:
            opened_files.append([row for row in csv.reader(f, delimiter=",")])

    print(opened_files)
    ordered_files_col = []
    for file_ in opened_files:
        ordered_files_col.append([[file_[j][i] for j in range(len(file_))] for i in range(len(file_[0]))])

    relativeDifference = [file_[-6:] for file_ in ordered_files_col]
    relativeDifference = [[sorted(row) for row in file_] for file_ in relativeDifference]
    relativeDifference = [[[(row[len(row)-1], row[i], i/(len(row)-1)) for i in range(len(row)-1)]for row in file_] for file_ in relativeDifference]

    for file_ in relativeDifference:
        for col in file_:
            xAxis = []
            yAxis = []
            for c, x, y in col:
                xAxis.append(x)
                yAxis.append(y)
            plt.plot(xAxis, yAxis)
            plt.show()
