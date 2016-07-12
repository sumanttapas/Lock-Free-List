import numpy
from sys import argv

lockfree = []
locks = []


def median(lst):
    return numpy.median(numpy.array(lst))

for i in range(1, 11):
    fptr = open("lockFree/LockFree"+str(i)+".txt", "r")
    s = fptr.read()
    lockfree.append(float(s))
    fptr.close()
for i in range(1, 11):
    fptr = open("locks/lock" + str(i) + ".txt", "r")
    s = fptr.read()
    locks.append(float(s))
    fptr.close()
lockfreeMedian = median(lockfree)
lockmedian = median(locks)
lockmean = numpy.mean(locks)
lockfreemean = numpy.mean(lockfree)
fptr = open("Final_Data_for_"+str(int(argv[1])/5)+"_queries.txt", "w")
fptr.write("Lock Free:" + str(lockfree))
fptr.write("\nLock Free:" + str(lockfree))
fptr.write("\nLocks:" + str(locks))
fptr.write("\nLock Free Median:" + str(lockfreeMedian))
fptr.write("\nLock Median:" + str(lockmedian))
fptr.write("\nLock Free Mean:" + str(lockfreemean))
fptr.write("\nLock Mean:" + str(lockmean))
fptr.close()
