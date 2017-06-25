import csv
import os
import sys

if __name__ == '__main__':
    directory_to_open = sys.argv[1]
    files = os.listdir(directory_to_open)
    file_csv = [directory_to_open+"/"+csv_ for csv_ in files if csv_.endswith(".csv")]
    csv_content = []
    for file_ in file_csv:
        with open(file_) as csv_file:
            spamreader = csv.reader(csv_file, delimiter=',')
            csv_content.append([line for line in spamreader])

    print(csv_content)
