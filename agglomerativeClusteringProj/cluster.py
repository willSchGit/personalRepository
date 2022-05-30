import os
from numpy import unravel_index
import re
import sys
import operator
import copy
import math
import time
import pathlib
import numpy
import scipy.spatial.distance as ssd
from scipy.cluster.hierarchy import dendrogram, linkage, ward, fcluster
from matplotlib import pyplot as plt
from sklearn.cluster import AgglomerativeClustering

path = '/afs/umbc.edu/users/w/i/willias1/home/476/phase4/files/'
outPath = '/afs/umbc.edu/users/w/i/willias1/home/476/outFile'

SCRUBR = re.compile('<.*?>|&([a-z0-9]+|#[0-9]{1,6}|#x[0-9a-f]{1,6});') #HTML symbols

stopDict = {} #defines the stoplist as a dictionary
stopFile = open('stoplist.txt', 'r')
words = stopFile.readlines()
count = 0
for line in words:
    stopDict[count] = line.strip()
    count += 1

def regexHTML(html):  #strips html tags
    txt = re.sub(SCRUBR, '', html)
    return txt

path = str(pathlib.Path().resolve()) + "/files/"

wordDict = {}
docDict = {}
fileDict = {}
postDict = {}
count = 1
freqDict = {}
for fileStream in os.listdir(path): #loops thro directories
    with open(os.path.join(path, fileStream), 'r', encoding="utf8", errors='ignore') as fileStream:
        for line in fileStream:
            tempString = regexHTML(line.strip()) #calls html stripper
            tempString = re.sub('[.@#$()",|]', '', tempString) #next lines strip different sets of symbols
            tempString = re.sub(r"[\([{})\]]", ' ', tempString)
            tempString = re.sub('[0-9]', '', tempString)
            tempString = re.sub('[%:;=!*?<>~&+_`]', '', tempString)
            tempString = re.sub('[-/]', ' ', tempString)
            tempString = re.sub('\x27', '', tempString)
        
            tempString = tempString.lower() #casts sting to lowercase
            for word in tempString.split(): #splits line into words
                if len(word) != 1 and word not in stopDict.values(): #checks stoplist
                    if word in wordDict.keys(): #if statement either adds new item to dict or updates the freqency
                        wordDict[word] = (wordDict[word] + 1)
                        if word in fileDict.keys():
                            fileDict[word] = (fileDict[word] + 1)
                        else:
                            fileDict[word] = 1
                            freqDict[word] = (freqDict[word] + 1)
                            postDict[word].append(count)
                    else:
                        wordDict[word] = 1
                        fileDict[word] = 1
                        freqDict[word] = 1
                        postDict[word] = [count]

        deepCopy = copy.deepcopy(fileDict) #makes a deep copy of the dictionary of the current file
        docDict[count] = deepCopy #adds deep copy to multidimentional dictionary
        fileDict.clear()
        count+=1


delList = [] #finds what words appear once in the whole corpus
for i in wordDict:
    if wordDict[i] == 1:
        delList.append(i)

for i in delList: #deletes those words from the corpus dictionary
    del wordDict[i]
    del freqDict[i]

for i in docDict.keys(): #deletes those words from the file specific dictionaries
    for j in delList:
        docDict[i].pop(j, None)


for i in docDict.keys(): #finds the term weights and normalizes them and updates the value of the dictionary to reflect the weight
    for j in docDict[i].keys():
        normVal = docDict[i][j]/len(docDict[i])
        #print(j)
        termFreq = math.log(count/freqDict[j])
        termWeight = normVal * termFreq
        docDict[i][j] = termWeight

#sorts the dictionary in alphabetical order
sortedFreq = dict(sorted(freqDict.items()))

#makes dictionary with token order and frequency from the sorted dictionary
invrtDict = {}
count = 0
for i in sortedFreq.keys():
    tempArr = []
    tempArr.append(sortedFreq[i])
    invrtDict[i] = tempArr
    if count == 0:
        invrtDict[i].append(1)
        count += 1
    else:
        count = count+sortedFreq[i]
        invrtDict[i].append(count)



#The 3 lines below set up the similatity scores matrix and the sum squares list
FILE_LENGTH = 503
weightList = [ [0]*FILE_LENGTH for i in range(FILE_LENGTH)]
sumList = [0]*FILE_LENGTH

#for loop that iterates through all the terms in the corpus
for i in invrtDict.keys():
    tempList = []
    count = 0

#for loop that iterates through every instance of a term
    for j in postDict[i]:
        temp = []
        temp.append(j)
        temp.append(docDict[j][i])
        tempList.append(temp)
#multplies the wieghts of every instance of a term that is below the current index
    while count != len(tempList)-1:
        numJ = tempList[count]
        numK = tempList[count]
        
        for x in range(count+1, len(tempList)):
            
            numK = tempList[x]
            weightList[numJ[0]-1][numK[0]-1] += numJ[1] * numK[1]
            weightList[numK[0]-1][numJ[0]-1] += numJ[1] * numK[1]
        
#calculates and adds up the values in the cum squares list
        count += 1
    if len(tempList) != 1:
        for x in tempList:
            sumList[x[0]-1] += x[1] * x[1]

#does the final equation of computing the sumsquares list with the weights to get the final similarity scores
for i in range(len(weightList)):
    for j in range(len(weightList[i])):
        if sumList[j] and sumList[i] != 0:
            weightList[i][j] /= math.sqrt(sumList[i])*math.sqrt(sumList[j])

#formats the similairty scores to be read by linkage
for i in range(len(weightList)):
    for j in range(len(weightList[i])):
        if i != j:
            weightList[i][j] = 1-weightList[i][j]

#formats the 2d structure itself to be fed to linkage
distArray = ssd.squareform(weightList)

test = linkage(distArray, 'single')


z = ward(distArray)
f = fcluster(test, t=0.6, criterion='distance')

#formats the output to be displayed and counts so the clusters can be numbered and named
count = 1
merge = 0
for i in z:
    if float(i[2]) < 0.6:
        if int(i[0]+1) > FILE_LENGTH and int(i[1]+1) > FILE_LENGTH:
            print("Line #",count, "Cluster on line", (int(i[0])+1)-FILE_LENGTH ," merged with Cluster on line", (int(i[1])+1)-FILE_LENGTH)
            count += 1
        elif int(i[0]+1) > FILE_LENGTH:
            print("Cluster ", (int(i[0])+1)-FILE_LENGTH ," merged with Document ", int(i[1])+1)
        elif int(i[1]+1) > FILE_LENGTH:
            print("Line #", count,"Document ", int(i[0])+1 ,"merged to cluster on line", (int(i[1])+1)-FILE_LENGTH)
            count += 1
        else:
            print("Line #",count,"Document ", int(i[0])+1 ," merged with Document ", int(i[1])+1)
            count += 1


