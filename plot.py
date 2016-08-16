from matplotlib import pyplot as plt
i = 100
lf_CPUtimeMedian = []
lf_IPCMedian = []
lf_L2MissesMedian = []
lf_L3MissesMedian = []
lf_L2HitsMedian = []
lf_L3HitsMedian = []
lf_CyclesMedian = []
lf_WallTimeMedian = []
# lf_BytesReadMedian = []
# lf_BytesWriteMedian = []

l_CPUtimeMedian = []
l_IPCMedian = []
l_L2MissesMedian = []
l_L3MissesMedian = []
l_L2HitsMedian = []
l_L3HitsMedian = []
l_CyclesMedian = []
l_BytesReadMedian = []
l_BytesWriteMedian = []
l_WallTimeMedian = []

# lf_WallTimeMedian = []
# l_WallTimeMean = []


while i < 5100:
    fname = "Final_Data_for_"+str(i)+"_queries.txt"
    f = open(fname, "r")
    s = f.read()
    f.close()
    l = s.splitlines()
    for line in l:
        y = line.split(":")
        if len(y) == 2:
            if y[0] == "Lock Free CPU Time Median":
                lf_CPUtimeMedian.append(float(y[1]))
            elif y[0] == "Lock Free IPC Median":
                lf_IPCMedian.append(float(y[1]))
            elif y[0] == "Lock Free L2 Misses Median":
                lf_L2MissesMedian.append(float(y[1]))
            elif y[0] == "Lock Free L3 Misses Median":
                lf_L3MissesMedian.append(float(y[1]))
            elif y[0] == "Lock Free L2 Hits Median":
                lf_L2HitsMedian.append(float(y[1]))
            elif y[0] == "Lock Free L3 Hits Median":
                lf_L3HitsMedian.append(float(y[1]))
            elif y[0] == "Lock Free Cycles Median":
                lf_CyclesMedian.append(float(y[1]))
            elif y[0] == "Lock Free wall Time":
                lf_WallTimeMedian.append(float(y[1]))
            # elif y[0] == "Lock Free Byte Read Median":
            #     lf_BytesReadMedian.append(float(y[1]))
            # elif y[0] == "Lock Free Byte Written Median":
            #     lf_BytesWriteMedian.append(float(y[1]))

            if y[0] == "Lock CPU Time Median":
                l_CPUtimeMedian.append(float(y[1]))
            elif y[0] == "Lock IPC Median":
                l_IPCMedian.append(float(y[1]))
            elif y[0] == "Lock L2 Misses Median":
                l_L2MissesMedian.append(float(y[1]))
            elif y[0] == "Lock L3 Misses Median":
                l_L3MissesMedian.append(float(y[1]))
            elif y[0] == "Lock L2 Hits Median":
                l_L2HitsMedian.append(float(y[1]))
            elif y[0] == "Lock L3 Hits Median":
                l_L3HitsMedian.append(float(y[1]))
            elif y[0] == "Lock Cycles Median":
                l_CyclesMedian.append(float(y[1]))
            elif y[0] == "Lock wall Time":
                l_WallTimeMedian.append(float(y[1]))
                # elif y[0] == "Lock Byte Read Median":
                #     l_BytesReadMedian.append(float(y[1]))
                # elif y[0] == "Lock Byte Written Median":
                #     l_BytesWriteMedian.append(float(y[1]))
    i += 100


x2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000, 3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500, 4600, 4700, 4800, 4900, 5000]
lol = []


'''fig1 = plt.figure(1)
plt.plot(x2, l_L3HitsMedian, label="Lock", color="c")
l1= plt.scatter(x2, l_L3HitsMedian, color="c")
plt.plot(x2, lf_L3HitsMedian, label="Lock Free", color="b")
l2= plt.scatter(x2, lf_L3HitsMedian, color="b")
plt.xlabel('Number of Insert Operations per thread')
plt.ylabel('Number of L3 Hits')
plt.title("L3 Hits Median")
plt.xlim(xmin=0)
plt.ylim(ymin=0)
lol.append(l1)
lol.append(l2)
fig1.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig2 = plt.figure(2)
plt.plot(x2, l_L2HitsMedian, label="Lock", color="c")
l1= plt.scatter(x2, l_L2HitsMedian, color="c")
plt.plot(x2, lf_L2HitsMedian, label="Lock Free", color="b")
l2= plt.scatter(x2, lf_L2HitsMedian, color="b")
plt.xlabel('Number of Insert Operations per thread')
plt.ylabel('Number of L2 Hits')
plt.title("L2 Hits Median")
lol.append(l1)
lol.append(l2)
fig2.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig3 = plt.figure(3)
plt.subplot(211)
plt.plot(x2, l_L2MissesMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_L2MissesMedian, color="c")
plt.plot(x2, lf_L2MissesMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_L2MissesMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('Number of L2 Misses')
plt.title("L2 Misses Median")

lol.append(l1)
lol.append(l2)
fig3.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig4 = plt.figure(4)
plt.plot(x2, l_CyclesMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_CyclesMedian, color="c")
plt.plot(x2, lf_CyclesMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_CyclesMedian, color="b")
plt.xlabel('Number of operations')
plt.title("Cycles Median")
lol.append(l1)
lol.append(l2)
plt.xlim(xmin=0)
plt.ylim(ymin=0)
fig4.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)'''

fig4 = plt.figure(4)
plt.plot(x2, l_WallTimeMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_WallTimeMedian, color="c")
plt.plot(x2, lf_WallTimeMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_WallTimeMedian, color="b")
plt.xlabel('Number of operations')
plt.title("Wall Time")
lol.append(l1)
lol.append(l2)
plt.xlim(xmin=0)
plt.ylim(ymin=0)
fig4.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)


'''fig5 = plt.figure(5)
plt.subplot(211)
plt.plot(x2, l_IPCMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_IPCMedian, color="c")
plt.plot(x2, lf_IPCMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_IPCMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('IPC')
plt.title("IPC Median")
lol.append(l1)
lol.append(l2)
fig5.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig6 = plt.figure(6)
plt.plot(x2, l_L3MissesMedian, label="Lock", color="c")
l1 = plt.scatter(x2, l_L3MissesMedian, color="c")
plt.plot(x2, lf_L3MissesMedian, label="Lock Free", color="b")
l2 = plt.scatter(x2, lf_L3MissesMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('Number of L3 Misses')
plt.title("L3 Misses Median")
lol.append(l1)
lol.append(l2)
fig6.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig7 = plt.figure(7)
plt.plot(x2, l_CPUtimeMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_CPUtimeMedian, color="c")
plt.plot(x2, lf_CPUtimeMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_CPUtimeMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('CPU Time')
plt.title("CPU Time Median")
plt.xlim(xmin=0)
plt.ylim(ymin=0)
lol.append(l1)
lol.append(l2)
fig7.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig8 = plt.figure(8)
plt.subplot(211)
plt.plot(x2, l_BytesReadMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_BytesReadMedian, color="c")
plt.plot(x2, lf_BytesReadMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_BytesReadMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('Number of Bytes Read')

plt.title("Bytes Read")

lol.append(l1)
lol.append(l2)
fig7.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)

fig9 = plt.figure(9)
plt.subplot(211)
plt.plot(x2, l_BytesWriteMedian, label="Lock", color="c")
l1=plt.scatter(x2, l_BytesWriteMedian, color="c")
plt.plot(x2, lf_BytesWriteMedian, label="Lock Free", color="b")
l2=plt.scatter(x2, lf_BytesWriteMedian, color="b")
plt.xlabel('Number of operations')
plt.ylabel('Number of Bytes Written')

plt.title("Bytes Written")

lol.append(l1)
lol.append(l2)
fig7.legend(handles=lol, labels=['lock', 'lock free'], loc='upper left', ncol=10)
lol.clear()
plt.subplots_adjust(hspace=0.38)'''

plt.show()

