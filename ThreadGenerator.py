from sys import argv


fptr = open(argv[1], 'r')
foutput = open("ListUsingLocks_"+argv[2]+"_threads.cpp", "w")
# file = fptr.read()
flag = 0
count = 0
body = "{\n"+"\tnode_t * head = (node_t *)args;\n"+"\tint d = (rand())%1000;\n"+"\tinsert(d,head);\n"+ \
       "\tinsert(d+2,head);\n"+"\tdeleteElement(head,d);\n"+"}"
for line in fptr.readlines():
    if "void * thread1(void *);" in line:
        for i in range(1, int(argv[2])+1):
            foutput.write("\nvoid * thread"+str(i)+"(void *);")
    elif "pthread_t t1;" in line:
        foutput.write("\n\tpthread_t ")
        for i in range(1, int(argv[2])+1):
            if i == int(argv[2]):
                foutput.write("t" + str(i) + ";\n")
            else:
                foutput.write("t" + str(i) + ", ")
    elif "pthread_create (&t1, NULL, thread2, (void *)head);" in line:
        for i in range(1, int(argv[2]) + 1):
            foutput.write("\n\tpthread_create (&t"+str(i)+", NULL, thread"+str(i)+", (void *)head);")
    elif "pthread_join (t1, NULL);" in line:
        for i in range(1, int(argv[2]) + 1):
            foutput.write("\n\tpthread_join (t"+str(i)+", NULL);")
    elif "void * thread1(void * args)" in line or flag == 1:
        break
    elif "pthread_create (" not in line and "void * thread" not in line and "pthread_join (" not in line:
        foutput.write(line)
for i in range(1, int(argv[2]) + 1):
    foutput.write("\nvoid * thread" + str(i) + "(void * args)\n")
    foutput.write(body)
fptr.close()
foutput.close()
