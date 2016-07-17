filename = '/home/flash/pcm/data/Time/result_LF.txt'
with open(filename,"r") as fout:
    for line in fout.readlines():
        ordered = sorted(float(filename))
        length = len(float(filename))
print("The median of this list is:")
print(float((ordered[length//2] + ordered[-(length+1)//2]))/2)
