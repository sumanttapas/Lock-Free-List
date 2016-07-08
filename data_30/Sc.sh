egrep -io "Time:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/Time/Time_LF.txt
egrep -io "Instructions per clock:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/IPC/IPC_LF.txt
egrep -io "Bytes read:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/BR/BR_LF.txt
egrep -io "Bytes Written:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/BW/BW_LF.txt
egrep -io "L2 Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/L2M/L2M_LF.txt
egrep -io "L2 HIts:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/L2H/L2H_LF.txt
egrep -io "L3 Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/L3M/L3M_LF.txt
egrep -io "L3 HIts:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/L3H/L3H_LF.txt
egrep -io "Cycles:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/Cycles/Cycles_LF.txt
egrep -io "Cycles Lost Due L3 Cache Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/CL3M/CL3M_LF.txt
egrep -io "Cycles Lost Due L2 Cache Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_LF-*.c > /home/flash/pcm/data/CL2M/CL2M_LF.txt
egrep -io "Time:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/Time/Time_WLF.txt
egrep -io "Instructions per clock:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/IPC/IPC_WLF.txt
egrep -io "Bytes read:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/BR/BR_WLF.txt
egrep -io "Bytes Written:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/BW/BW_WLF.txt
egrep -io "L2 Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/L2M/L2M_WLF.txt
egrep -io "L2 HIts:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/L2H/L2H_WLF.txt
egrep -io "L3 Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/L3M/L3M_WLF.txt
egrep -io "L3 HIts:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/L3H/L3H_WLF.txt
egrep -io "Cycles:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/Cycles/Cycles_WLF.txt
egrep -io "Cycles Lost Due L3 Cache Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/CL3M/CL3M_WLF.txt
egrep -io "Cycles Lost Due L2 Cache Misses:[A-Z0-9.-]+.[A-Z0-9.-]" *_WLF-*.c > /home/flash/pcm/data/CL2M/CL2M_WLF.txt
cut -c31- /home/flash/pcm/data/Time/Time_LF.txt > /home/flash/pcm/data/Time/result_LF.txt
cut -c49- /home/flash/pcm/data/IPC/IPC_LF.txt >   /home/flash/pcm/data/IPC/result_LF.txt
cut -c37- /home/flash/pcm/data/BR/BR_LF.txt > /home/flash/pcm/data/BR/result_LF.txt
cut -c40- /home/flash/pcm/data/BW/BW_LF.txt > /home/flash/pcm/data/BW/result_LF.txt
cut -c36- /home/flash/pcm/data/L2M/L2M_LF.txt > /home/flash/pcm/data/L2M/result_LF.txt
cut -c34- /home/flash/pcm/data/L2H/L2H_LF.txt > /home/flash/pcm/data/L2H/result_LF.txt
cut -c36- /home/flash/pcm/data/L3M/L3M_LF.txt > /home/flash/pcm/data/L3M/result_LF.txt
cut -c34- /home/flash/pcm/data/L3H/L3H_LF.txt > /home/flash/pcm/data/L3H/result_LF.txt
cut -c33- /home/flash/pcm/data/Cycles/Cycles_LF.txt > /home/flash/pcm/data/Cycles/result_LF.txt
cut -c58- /home/flash/pcm/data/CL3M/CL3M_LF.txt > /home/flash/pcm/data/CL3M/result_LF.txt
cut -c58- /home/flash/pcm/data/CL2M/CL2M_LF.txt > /home/flash/pcm/data/CL2M/result_LF.txt
cut -c32- /home/flash/pcm/data/Time/Time_WLF.txt > /home/flash/pcm/data/Time/result_WLF.txt
cut -c50- /home/flash/pcm/data/IPC/IPC_WLF.txt >   /home/flash/pcm/data/IPC/result_WLF.txt
cut -c38- /home/flash/pcm/data/BR/BR_WLF.txt > /home/flash/pcm/data/BR/result_WLF.txt
cut -c41- /home/flash/pcm/data/BW/BW_WLF.txt > /home/flash/pcm/data/BW/result_WLF.txt
cut -c37- /home/flash/pcm/data/L2M/L2M_WLF.txt > /home/flash/pcm/data/L2M/result_WLF.txt
cut -c35- /home/flash/pcm/data/L2H/L2H_WLF.txt > /home/flash/pcm/data/L2H/result_WLF.txt
cut -c37- /home/flash/pcm/data/L3M/L3M_WLF.txt > /home/flash/pcm/data/L3M/result_WLF.txt
cut -c35- /home/flash/pcm/data/L3H/L3H_WLF.txt > /home/flash/pcm/data/L3H/result_WLF.txt
cut -c34- /home/flash/pcm/data/Cycles/Cycles_WLF.txt > /home/flash/pcm/data/Cycles/result_WLF.txt
cut -c59- /home/flash/pcm/data/CL3M/CL3M_WLF.txt > /home/flash/pcm/data/CL3M/result_WLF.txt
cut -c59- /home/flash/pcm/data/CL2M/CL2M_WLF.txt > /home/flash/pcm/data/CL2M/result_WLF.txt
python /home/flash/pcm/data/test.py > /home/flash/pcm/data/Final_data_LF.c
python /home/flash/pcm/data/test1.py > /home/flash/pcm/data/Final_data_WLF.c



