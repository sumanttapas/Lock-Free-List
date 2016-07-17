#! /usr/bin/env Rscript
sink('/home/flash/pcm/data/Final_m_wlf.c')
d<-scan("/home/flash/pcm/data/L3M/result_WLF.txt", quiet=TRUE)
cat("Median of L3 Misses=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/L2M/result_WLF.txt", quiet=TRUE)
cat("Median of L2 Misses=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/L3H/result_WLF.txt", quiet=TRUE)
cat("Median of L3 Hits=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/L2H/result_WLF.txt", quiet=TRUE)
cat("Median of L2 Hits=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/Time/result_WLF.txt", quiet=TRUE)
cat("Median of Time=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/Cycles/result_WLF.txt", quiet=TRUE)
cat("Median of Cycles=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/IPC/result_WLF.txt", quiet=TRUE)
cat("Median of IPC=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/CL3M/result_WLF.txt", quiet=TRUE)
cat("Median of CL3M=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/CL2M/result_WLF.txt", quiet=TRUE)
cat("Median of CL2M=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/BR/result_WLF.txt", quiet=TRUE)
cat("Median of Bytes Read=")
cat(median(d), sep="\n")
d<-scan("/home/flash/pcm/data/BW/result_WLF.txt", quiet=TRUE)
cat("Median of Bytes Written=")
cat(median(d), sep="\n")
# Stop writing to the file
sink()
# Append to the file
sink('/home/flash/pcm/data/Final_m_wlf.c', append=TRUE)
sink()
