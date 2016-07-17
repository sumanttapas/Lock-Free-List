from __future__ import with_statement
import os
data = []
data1 = []
data2 = []
data3 = []
data4 = []
data5 = []
data6 = []
data7 = []
data8 = []
data9 = []
data10 = []
with open(r'/home/flash/pcm/data/Time/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data.extend(rowdata)

print("Average Time:"+ str(sum(data)/len(data)))
with open(r'/home/flash/pcm/data/IPC/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data1.extend(rowdata)

print("Average Bytes IPC:"+ str(sum(data1)/len(data1)))
with open(r'/home/flash/pcm/data/BR/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data2.extend(rowdata)

print("Average Bytes read:"+ str(sum(data2)/len(data2)))
with open(r'/home/flash/pcm/data/BW/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data3.extend(rowdata)

print("Average Bytes Written:"+ str(sum(data3)/len(data3)))
with open(r'/home/flash/pcm/data/L2M/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data4.extend(rowdata)

print("Average L2 Misses:"+ str(sum(data4)/len(data4)))
with open(r'/home/flash/pcm/data/L3M/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data6.extend(rowdata)

print("Average L3 Misses:"+ str(sum(data6)/len(data6)))
with open(r'/home/flash/pcm/data/L2H/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data5.extend(rowdata)

print("Average L2 Hits:"+ str(sum(data5)/len(data5)))
with open(r'/home/flash/pcm/data/L3H/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data7.extend(rowdata)

print("Average L3 Hits:"+ str(sum(data7)/len(data7)))
with open(r'/home/flash/pcm/data/Cycles/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data8.extend(rowdata)

print("Average Cycles:"+ str(sum(data8)/len(data8)))
with open(r'/home/flash/pcm/data/CL3M/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data9.extend(rowdata)

print("Average CL3M:"+ str(sum(data9)/len(data9)))
with open(r'/home/flash/pcm/data/CL2M/result_LF.txt') as f:
    for line in f:
        fields = line.split()
        rowdata = map(float, fields)
        data10.extend(rowdata)

print("Average CL2M:"+ str(sum(data10)/len(data10)))

