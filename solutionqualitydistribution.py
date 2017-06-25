import csv
import os
import sys

def genRelativeDifference(csv_res):
    new_file = []
    new_file.append(csv_res[0]+["d1", "d2", "d3", "d4", "d5", "d6"])
    for row in csv_res[1:]:
        new_file.append(row+[abs(float(el)-float(row[7]))/float(row[7]) for el in row[1:-1]])
    return new_file

if __name__ == '__main__':
    directory_to_open = sys.argv[1]
    files = os.listdir(directory_to_open)
    file_csv = [directory_to_open+"/"+csv_ for csv_ in files if csv_.endswith(".csv")]
    csv_content = []
    for file_ in file_csv:
        with open(file_) as csv_file:
            spamreader = csv.reader(csv_file, delimiter=',')
            csv_content.append([line for line in spamreader])

    new_res = []
    for csv_res in csv_content:
        res = genRelativeDifference(csv_res)
        new_res.append(res)
    to_write = zip(file_csv, new_res)
    for file_, csv_ in to_write:
        file_to_open = open(file_[:-4]+"SQD.csv", 'w')
        writer = csv.writer(file_to_open, delimiter=',')
        for row in csv_:
            writer.writerow(row)
