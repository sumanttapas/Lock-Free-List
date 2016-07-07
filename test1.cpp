#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include "cpucounters.h"
#include <time.h>


typedef struct node
{
	int data;
	struct node* next;
}node_t;

int c=0;

void *thread1(void *);
void *thread2(void *);
void *thread3(void *);
void *thread4(void *);
void *thread5(void *);
void *thread6(void *);
void *thread7(void *);
void *thread8(void *);
void *thread9(void *);
void *thread10(void *);
void *thread11(void *);
void *thread12(void *);
void *thread13(void *);
void *thread14(void *);
void *thread15(void *);
void *thread16(void *);
void *thread17(void *);
void *thread18(void *);
void *thread19(void *);
void *thread20(void *);


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void insert(int data,node_t * head)
{

	pthread_mutex_lock(&mutex);
	node_t * next = head->next;
	node_t * curr = head;


	while(next->data <= data)
	{
		curr = next;
		next = next->next;
	}
	if(curr->data != data)
	{
		node_t * n = (node_t *)malloc(sizeof(struct node));
		n->data = data;
		//
		n->next = next;
		curr->next = n;
		//pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_unlock(&mutex);
}

void printlist(node_t * head)
{
	head = head->next;
	while(head->data != 10000)
	{
		printf("%d\n",head->data);
		head = head->next;
	}
}

int deleteElement(node_t *head, int data)
{
	pthread_mutex_lock(&mutex);
	node_t * next = head->next;
	node_t * curr = head;


	while(next->data <= data-0.2)
	{
		curr = next;
		next = next->next;
	}
	if(next->data != data)
		return -1;
	curr->next = next->next;
	free(next);
	pthread_mutex_unlock(&mutex);
	return 1;
}

node_t *init_list()
{
	node_t * head = (node_t *)malloc(sizeof(node_t));
	node_t * tail = (node_t *)malloc(sizeof(node_t));
	head->next = tail;
	head->data = -10000;
	tail->data = 10000;
	return head;
}

int main(void)
{
	PCM * m = PCM::getInstance();
	PCM::ErrorCode returnResult = m->program();
	if (returnResult != PCM::Success){
	  std::cerr << "Intel's PCM couldn't start" << std::endl;
	  std::cerr << "Error code: " << returnResult << std::endl;
	  exit(1);
	}
	clock_t begin = clock();	
	node_t * head = init_list();
	SystemCounterState before_sstate = getSystemCounterState();
	pthread_t t1,t2,t3,t4,t5,t6,t7,t8,t9,t10,t11,t12,t13,t14,t15,t16,t17,t18,t19,t20;
	pthread_create (&t2, NULL, thread2, (void *)head);
	pthread_create (&t1, NULL, thread1, (void *)head);
	pthread_create (&t3, NULL, thread3, (void *)head);
	pthread_create (&t4, NULL, thread4, (void *)head);
	pthread_create (&t5, NULL, thread5, (void *)head);
	pthread_create (&t6, NULL, thread6, (void *)head);
	pthread_create (&t7, NULL, thread7, (void *)head);
	pthread_create (&t8, NULL, thread8, (void *)head);
	pthread_create (&t9, NULL, thread9, (void *)head);
	pthread_create (&t10, NULL, thread10, (void *)head);
	pthread_create (&t11, NULL, thread11, (void *)head);
	pthread_create (&t12, NULL, thread12, (void *)head);
	pthread_create (&t13, NULL, thread13, (void *)head);
	pthread_create (&t14, NULL, thread14, (void *)head);
	pthread_create (&t15, NULL, thread15, (void *)head);
	pthread_create (&t16, NULL, thread16, (void *)head);
	pthread_create (&t17, NULL, thread17, (void *)head);
	pthread_create (&t18, NULL, thread18, (void *)head);
	pthread_create (&t19, NULL, thread19, (void *)head);
	pthread_create (&t20, NULL, thread20, (void *)head);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	pthread_join (t3, NULL);
	pthread_join (t4, NULL);
	pthread_join (t5, NULL);
	pthread_join (t6, NULL);
	pthread_join (t7, NULL);
	pthread_join (t8, NULL);
	pthread_join (t9, NULL);
	pthread_join (t10, NULL);
	pthread_join (t11, NULL);
	pthread_join (t12, NULL);
	pthread_join (t13, NULL);
	pthread_join (t14, NULL);
	pthread_join (t15, NULL);
	pthread_join (t16, NULL);
	pthread_join (t17, NULL);
	pthread_join (t18, NULL);
	pthread_join (t19, NULL);
	pthread_join (t20, NULL);
	SystemCounterState after_sstate = getSystemCounterState();
	clock_t end = clock();
	double time_s = (double)(end-begin)/ CLOCKS_PER_SEC;

	std::cout << "\nTime:" << time_s << std::endl;
	std::cout << "\nInstructions per clock:" << getIPC(before_sstate,after_sstate) << std::endl;
	std::cout << "Bytes read:" << getBytesReadFromMC(before_sstate,after_sstate) << std::endl;
	std::cout << "Bytes Written:" << getBytesWrittenToMC(before_sstate,after_sstate) << std::endl;

	std::cout << "L2 Misses:" << getL2CacheMisses(before_sstate,after_sstate)<< std::endl;
	std::cout << "L2 HIts:" << getL2CacheHits(before_sstate,after_sstate)<< std::endl;
	std::cout << "L3 Misses:" << getL3CacheMisses(before_sstate,after_sstate)<< std::endl;
	std::cout << "L3 HIts:" << getL3CacheHits(before_sstate,after_sstate)<< std::endl;
	std::cout << "Cycles:" << getCycles(before_sstate,after_sstate)<<std::endl;
	std::cout << "Cycles Lost Due L3 Cache Misses:" << getCyclesLostDueL3CacheMisses(before_sstate,after_sstate)<<std::endl;
	std::cout << "Cycles Lost Due L2 Cache Misses:" << getCyclesLostDueL2CacheMisses(before_sstate,after_sstate)<<std::endl;
	printlist(head);
	return 0;
}

void * thread1(void * args)
{
	node_t * head = (node_t *)args;
	insert(12,head);
	insert(14,head);
	deleteElement(head,12);
	//deleteElement(head,0);
}

void * thread2(void * args)
{
	node_t * head = (node_t *)args;
	insert(16,head);
	insert(18,head);
	deleteElement(head,16);
	//deleteElement(head,1);
}

void * thread3(void * args)
{
	node_t * head = (node_t *)args;
	insert(10,head);
	insert(8,head);
	deleteElement(head,10);
	//deleteElement(head,0);
}
void * thread4(void * args)
{
	node_t * head = (node_t *)args;
	insert(6,head);
	insert(4,head);
	deleteElement(head,6);
	//deleteElement(head,0);
}
void * thread5(void * args)
{
	node_t * head = (node_t *)args;
	insert(2,head);
	insert(0,head);
	deleteElement(head,2);
	//deleteElement(head,0);
}
void * thread6(void * args)
{
	node_t * head = (node_t *)args;
	insert(20,head);
	insert(22,head);
	deleteElement(head,20);
	//deleteElement(head,0);
}
void * thread7(void * args)
{
	node_t * head = (node_t *)args;
	insert(120,head);
	insert(122,head);
	deleteElement(head,120);
	//deleteElement(head,0);
}

void * thread8(void * args)
{
	node_t * head = (node_t *)args;
	insert(201,head);
	insert(221,head);
	deleteElement(head,201);
	//deleteElement(head,1);
}

void * thread9(void * args)
{
	node_t * head = (node_t *)args;
	insert(9,head);
	insert(19,head);
	deleteElement(head,9);
	//deleteElement(head,0);
}
void * thread10(void * args)
{
	node_t * head = (node_t *)args;
	insert(39,head);
	insert(49,head);
	deleteElement(head,39);
	//deleteElement(head,0);
}
void * thread11(void * args)
{
	node_t * head = (node_t *)args;
	insert(69,head);
	insert(79,head);
	deleteElement(head,69);
	//deleteElement(head,0);
}
void * thread12(void * args)
{
	node_t * head = (node_t *)args;
	insert(99,head);
	insert(109,head);
	deleteElement(head,99);
	//deleteElement(head,0);
}
void * thread13(void * args)
{
	node_t * head = (node_t *)args;
	insert(129,head);
	insert(139,head);
	deleteElement(head,129);
	//deleteElement(head,0);
}
void * thread14(void * args)
{
	node_t * head = (node_t *)args;
	insert(159,head);
	insert(169,head);
	deleteElement(head,159);
	//deleteElement(head,0);
}
void * thread15(void * args)
{
	node_t * head = (node_t *)args;
	insert(189,head);
	insert(199,head);
	deleteElement(head,189);
	//deleteElement(head,0);
}
void * thread16(void * args)
{
	node_t * head = (node_t *)args;
	insert(219,head);
	insert(229,head);
	deleteElement(head,219);
	//deleteElement(head,0);
}
void * thread17(void * args)
{
	node_t * head = (node_t *)args;
	insert(200,head);
	insert(190,head);
	deleteElement(head,200);
	//deleteElement(head,0);
}
void * thread18(void * args)
{
	node_t * head = (node_t *)args;
	insert(170,head);
	insert(160,head);
	deleteElement(head,170);
	//deleteElement(head,0);
}
void * thread19(void * args)
{
	node_t * head = (node_t *)args;
	insert(140,head);
	insert(130,head);
	deleteElement(head,140);
	//deleteElement(head,0);
}
void * thread20(void * args)
{
	node_t * head = (node_t *)args;
	insert(145,head);
	insert(155,head);
	deleteElement(head,145);
	//deleteElement(head,0);
}
