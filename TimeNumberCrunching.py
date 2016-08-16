import numpy
from sys import argv

lf_time = []
lf_IPC = []
lf_L2_Misses = []
lf_L3_Misses = []
lf_L2Hits = []
lf_L3Hits = []
lf_Cylces = []
lf_bytes_read=[]
lf_bytes_written=[]
lf_wallTime = []

l_time = []
l_IPC = []
l_L2_Misses = []
l_L3_Misses = []
l_L2Hits = []
l_L3Hits = []
l_Cylces = []
l_bytes_read=[]
l_bytes_written=[]
l_wallTime = []

def median(lst):
    return numpy.median(numpy.array(lst))

for i in range(1, 6):
    fptr = open("lockFree/LockFree"+str(i)+".txt", "r")
    s = fptr.read()
    for line in s.splitlines():
        y = line.split(":")
        if len(y) == 2:
            if y[0] == "CPU Time":
                lf_time.append(float(y[1]))
            elif y[0] == "Instructions per clock":
                lf_IPC.append(float(y[1]))
            elif y[0] == "L2 Misses":
                lf_L2_Misses.append(float(y[1]))
            elif y[0] == "L2 HIts":
                lf_L2Hits.append(float(y[1]))
            elif y[0] == "L3 Misses":
                lf_L3_Misses.append(float(y[1]))
            elif y[0] == "L3 HIts":
                lf_L3Hits.append(float(y[1]))
            elif y[0] == "Cycles":
                lf_Cylces.append(float(y[1]))
            elif y[0] == "Bytes Read":
                lf_bytes_read.append(float(y[1]))
            elif y[0] == "Bytes Written":
                lf_bytes_written.append(float(y[1]))
        if "real" in line:
            test = line[len(line)-6:]
            lf_wallTime.append(float(test[:len(test)-1]))

    fptr.close()

    fptr1 = open("locks/lock" + str(i) + ".txt", "r")
    s1 = fptr1.read()
    for line in s1.splitlines():
        y1 = line.split(":")
        if len(y1) == 2:
            if y1[0] == "CPU Time":
                l_time.append(float(y1[1]))
            elif y1[0] == "Instructions per clock":
                l_IPC.append(float(y1[1]))
            elif y1[0] == "L2 Misses":
                l_L2_Misses.append(float(y1[1]))
            elif y1[0] == "L2 HIts":
                l_L2Hits.append(float(y1[1]))
            elif y1[0] == "L3 Misses":
                l_L3_Misses.append(float(y1[1]))
            elif y1[0] == "L3 HIts":
                l_L3Hits.append(float(y1[1]))
            elif y1[0] == "Cycles":
                l_Cylces.append(float(y1[1]))
            elif y1[0] == "Bytes Read":
                l_bytes_read.append(float(y1[1]))
            elif y1[0] == "Bytes Written":
                l_bytes_written.append(float(y1[1]))
        if "real" in line:
            test = line[len(line) - 6:]
            l_wallTime.append(float(test[:len(test) - 1]))
    fptr.close()
# lf_time_median = median(lf_time)
# lf_IPC_median = median(lf_IPC)
# lf_L2_Misses_median = median(lf_L2_Misses)
# lf_L3_Misses_median = median(lf_L3_Misses)
# lf_L2Hits_median = median(lf_L2Hits)
# lf_L3Hits_median = median(lf_L3Hits)
# lf_Cylces_median = median(lf_Cylces)
lf_wallTime_median = median(lf_wallTime)
# lf_bytes_read_median=median(lf_bytes_read)
# lf_bytes_written_median=median(lf_bytes_written)
# lf_Cylces.sort()
# l_time_median = median(l_time)
# l_IPC_median = median(l_IPC)
# l_L2_Misses_median = median(l_L2_Misses)
# l_L3_Misses_median = median(l_L3_Misses)
# l_L2Hits_median = median(l_L2Hits)
# l_L3Hits_median = median(l_L3Hits)
# l_Cylces_median = median(l_Cylces)
l_wallTime_median = median(l_wallTime)
# l_bytes_read_median=median(l_bytes_read)
# l_bytes_written_median=median(l_bytes_written)

fptr = open("Final_Data_for_"+str(int(argv[1]))+"_queries.txt", "w")

# fptr.write("\nLock Free CPU Time Median:" + str(lf_time_median))
# fptr.write("\nLock Free IPC Median:" + str(lf_IPC_median))
# fptr.write("\nLock Free L2 Misses Median:" + str(lf_L2_Misses_median))
# fptr.write("\nLock Free L3 Misses Median:" + str(lf_L3_Misses_median))
# fptr.write("\nLock Free L2 Hits Median:" + str(lf_L2Hits_median))
# fptr.write("\nLock Free L3 Hits Median:" + str(lf_L3Hits_median))
# fptr.write("\nLock Free Cycles Median:" + str(lf_Cylces_median))
fptr.write("\nLock Free wall Time:" + str(lf_wallTime_median))
# fptr.write("\nLock Free Bytes Read Median:" + str(lf_bytes_read_median))
# fptr.write("\nLock Free Bytes Written Median:" + str(lf_bytes_written_median))

# fptr.write("\nLock CPU Time Median:" + str(l_time_median))
# fptr.write("\nLock IPC Median:" + str(l_IPC_median))
# fptr.write("\nLock L2 Misses Median:" + str(l_L2_Misses_median))
# fptr.write("\nLock L3 Misses Median:" + str(l_L3_Misses_median))
# fptr.write("\nLock L2 Hits Median:" + str(l_L2Hits_median))
# fptr.write("\nLock L3 Hits Median:" + str(l_L3Hits_median))
# fptr.write("\nLock Cycles Median:" + str(l_Cylces_median))
fptr.write("\nLock wall Time:" + str(l_wallTime_median))
# fptr.write("\nLock Bytes Read Median:" + str(l_bytes_read_median))
# fptr.write("\nLock Bytes Written Median:" + str(l_bytes_written_median))
fptr.close()
