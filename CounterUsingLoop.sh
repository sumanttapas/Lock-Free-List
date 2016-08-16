for i in 100 200 300 400 500 600 700 800 900 1000 1100 1200 1300 1400 1500 1600 1700 1800 1900 2000 2100 2200 2300 2400 2500 2600 2700 2800 2900 3000 3100 3200 3300 3400 3500 3600 3700 3800 3900 4000 4100 4200 4300 4400 4500 4600 4700 4800 4900 5000
do
	#echo "compling for $i"
	tp="_queries_per_thread.cpp"
	filename="LockFreeListFinal4Threads_$i$tp"
	g++ -o myfree -std=c++11 -I ./pcm/ -L ./cpucounters.o ./pci.o ./msr.o ./client_bw.o ./cpucounters.o -lpthread $filename
	filename="ListUsingLocks_4_threads_$i$tp"
	g++ -o mylocks -std=c++11 -I ./pcm/ -L ./cpucounters.o ./pci.o ./msr.o ./client_bw.o ./cpucounters.o -lpthread $filename
	
	#echo lock Free
	for k in 1 2 3 4 5
	do
		fname="LockFree$k.txt"		
		(time ./myfree) &>lockFree/$fname
	done
	
	#echo locks
	for k in 1 2 3 4 5
	do
		fname="lock$k.txt"		
		(time ./mylocks) &>locks/$fname
	done
	
	#echo Calling Python script to store numbers
	python3 TimeNumberCrunching.py $i
done
python3 plot.py
