rm -rf lockFree
rm -rf locks
mkdir lockFree
mkdir locks
echo generating c 100 queires
python3 numberofqueries.py LockFreeListFinal4Threads.cpp 100
python3 numberofqueries.py ListUsingLocks_4_threads.cpp 100
echo compling..
g++ LockFreeListFinal4Threads_100_queries_per_thread.cpp -o latest -lpthread
g++ ListUsingLocks_4_threads_100_queries_per_thread.cpp -o latestusinglocks -lpthread
echo lock Free
./latest &>lockFree/LockFree1.txt
./latest &>lockFree/LockFree2.txt
./latest &>lockFree/LockFree3.txt
./latest &>lockFree/LockFree4.txt
./latest &>lockFree/LockFree5.txt
./latest &>lockFree/LockFree6.txt
./latest &>lockFree/LockFree7.txt
./latest &>lockFree/LockFree8.txt
./latest &>lockFree/LockFree9.txt
./latest &>lockFree/LockFree10.txt
echo Using Locks
./latestusinglocks &>locks/lock1.txt
./latestusinglocks &>locks/lock2.txt
./latestusinglocks &>locks/lock3.txt
./latestusinglocks &>locks/lock4.txt
./latestusinglocks &>locks/lock5.txt
./latestusinglocks &>locks/lock6.txt
./latestusinglocks &>locks/lock7.txt
./latestusinglocks &>locks/lock8.txt
./latestusinglocks &>locks/lock9.txt
./latestusinglocks &>locks/lock10.txt
echo Calling Python script to store numbers
python3 TimeNumberCrunching.py 100

echo generating c 1000 queires
python3 numberofqueries.py LockFreeListFinal4Threads.cpp 1000
python3 numberofqueries.py ListUsingLocks_4_threads.cpp 1000
echo compling..
g++ LockFreeListFinal4Threads_1000_queries_per_thread.cpp -o latest -lpthread
g++ ListUsingLocks_4_threads_1000_queries_per_thread.cpp -o latestusinglocks -lpthread
echo lock Free
./latest &>lockFree/LockFree1.txt
./latest &>lockFree/LockFree2.txt
./latest &>lockFree/LockFree3.txt
./latest &>lockFree/LockFree4.txt
./latest &>lockFree/LockFree5.txt
./latest &>lockFree/LockFree6.txt
./latest &>lockFree/LockFree7.txt
./latest &>lockFree/LockFree8.txt
./latest &>lockFree/LockFree9.txt
./latest &>lockFree/LockFree10.txt
echo Using Locks
./latestusinglocks &>locks/lock1.txt
./latestusinglocks &>locks/lock2.txt
./latestusinglocks &>locks/lock3.txt
./latestusinglocks &>locks/lock4.txt
./latestusinglocks &>locks/lock5.txt
./latestusinglocks &>locks/lock6.txt
./latestusinglocks &>locks/lock7.txt
./latestusinglocks &>locks/lock8.txt
./latestusinglocks &>locks/lock9.txt
./latestusinglocks &>locks/lock10.txt
echo Calling Python script to store numbers
python3 TimeNumberCrunching.py 1000

echo generating c 5000 queires
python3 numberofqueries.py LockFreeListFinal4Threads.cpp 5000
python3 numberofqueries.py ListUsingLocks_4_threads.cpp 5000
echo compling..
g++ LockFreeListFinal4Threads_5000_queries_per_thread.cpp -o latest -lpthread
g++ ListUsingLocks_4_threads_5000_queries_per_thread.cpp -o latestusinglocks -lpthread
echo lock Free
./latest &>lockFree/LockFree1.txt
./latest &>lockFree/LockFree2.txt
./latest &>lockFree/LockFree3.txt
./latest &>lockFree/LockFree4.txt
./latest &>lockFree/LockFree5.txt
./latest &>lockFree/LockFree6.txt
./latest &>lockFree/LockFree7.txt
./latest &>lockFree/LockFree8.txt
./latest &>lockFree/LockFree9.txt
./latest &>lockFree/LockFree10.txt
echo Using Locks
./latestusinglocks &>locks/lock1.txt
./latestusinglocks &>locks/lock2.txt
./latestusinglocks &>locks/lock3.txt
./latestusinglocks &>locks/lock4.txt
./latestusinglocks &>locks/lock5.txt
./latestusinglocks &>locks/lock6.txt
./latestusinglocks &>locks/lock7.txt
./latestusinglocks &>locks/lock8.txt
./latestusinglocks &>locks/lock9.txt
./latestusinglocks &>locks/lock10.txt
echo Calling Python script to store numbers
python3 TimeNumberCrunching.py 5000




