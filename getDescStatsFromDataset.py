import sys
import os
import csv
from statistics import *

dict_val = {"d1": "firstfit", "d2": "firstfitdecreasing", "d3": "MBS", "d4": "MBS'", "d5": "MBS samipling", "d6": "VNS"}

def transpose(data):
    return [[data[x][y] for x in range(len(data))]for y in range(len(data[0]))]

def genStats(file_):
    with open(file_, "r") as f:
        data = [line for line in csv.reader(f, delimiter=",")]
    data = [[data[x][y] for x in range(len(data))]for y in range(len(data[0]))]
    dataToCheck = data[8:]
    results = [["stats", "media", "varianza"]]
    for col in dataToCheck:
        el = [dict_val[col[0]], mean([float(val) for val in col[1:]]), variance([float(val) for val in col[1:]])]
        results.append(el)
    results = transpose(results)
    with open(file_.split("txtSQD")[0]+"stats.csv", "w") as f:
        wr = csv.writer(f, delimiter=",")
        for r in results:
            wr.writerow(r)


if __name__ == '__main__':
    directory_to_open = sys.argv[1]
    files = os.listdir(directory_to_open)
    file_csv = [directory_to_open+"/"+csv_ for csv_ in files if csv_.endswith("SQD.csv")]

    for file_ in file_csv:
        genStats(file_)
