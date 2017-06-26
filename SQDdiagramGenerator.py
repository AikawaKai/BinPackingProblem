import sys
import os
import csv
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

dict_class = {"d1":"firstfit", "d2":"firstfitdecreasing", "d3": "MBS", "d4":"MBS'", "d5":"MBS'sampling", "d6": "VNS"}
colors = ["r", "g", "b", "y", "k", "m"]


if __name__ == '__main__':

    path = sys.argv[1]
    files = os.listdir(path)
    files = [path+"/"+file_ for file_ in files if file_.endswith("SQD.csv")]
    titles = [file_.split(".txt")[0].split("//")[1] for file_ in files]
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
    j = 0;
    for file_ in relativeDifference:
        title = titles[j]
        i=0;
        patches = []
        for col in file_:
            xAxis = []
            yAxis = []
            for c, x, y in col:
                xAxis.append(x)
                yAxis.append(y)
            class_patch = mpatches.Patch(color=colors[i], label=dict_class[c])
            patches.append(class_patch)
            plt.plot(xAxis, yAxis, colors[i])
            i+=1
        j+=1;
        plt.title('Solution Quality Distribution '+title)
        plt.legend(bbox_to_anchor=(1, 1), loc=2, handles=patches)
        plt.show()
