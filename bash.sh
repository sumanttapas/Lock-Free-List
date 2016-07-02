g++ -std=c++11 -I ./pcm/ -L ./cpucounters.o ./pci.o ./msr.o ./client_bw.o ./cpucounters.o -lpthread  Lockfreelist_x86_64.cpp -o lff
./lff &>output.txt
sed '16q;d' output.txt &>data.txt
if cmp -s "data.txt" "expected.txt"
then
   echo "Code Correct!!!"
else
   echo "Something wrong!!!"
fi

