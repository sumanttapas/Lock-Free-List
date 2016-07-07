/*
 ============================================================================
 Name        : Linkedlist.c
 Author      : Sumant
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

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

	node_t * last = head;
	pthread_mutex_lock(&mutex);
	c++;
	while(last->next != NULL)
	{
		last = last->next;
	}
	if(last == head && c == 1)
	{
		last->data = data;
	}
	else if(c>1)
	{
		node_t * n = (node_t *)malloc(sizeof(struct node));
		n->data = data;
		//
		last->next = n;
		n->next = NULL;
		//pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_unlock(&mutex);

}

void printlist(node_t * head)
{
	do
	{
		printf("\t%d\n",head->data);
		head = head->next;
	}while(head != NULL);
}

void deleteElement(node_t *head, int pos)
{
	int var;
	node_t * prev;
	node_t * node = head;
	node_t head1 = *head;
	pthread_mutex_lock(&mutex);
	for (var = 0; var < pos; ++var)
	{
		prev = node;
		node = node->next;
	}
	if(node == head)
	{
		node_t * temp = head->next;
		*head = *temp;
		free(temp);
	}
	else
	{
		prev->next = node->next;
		free(node);
	}
	pthread_mutex_unlock(&mutex);
}

node_t *init_list()
{
	node_t * head = (node_t *)malloc(sizeof(node_t));
	head->next = NULL;
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
	SystemCounterState before_sstate = getSystemCounterState();
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	pthread_join (t3, NULL);
	pthread_join (t4, NULL);
	pthread_join (t5, NULL);
	pthread_join (t6, NULL);
	clock_t end = clock();
	double time_s = (double)(end-begin)/ CLOCKS_PER_SEC;
	SystemCounterState after_sstate = getSystemCounterState();

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
	insert(53,head);
	//deleteElement(head,0);
}

void * thread2(void * args)
{
	node_t * head = (node_t *)args;
	insert(16,head);
	insert(18,head);
	insert(43,head);
	//deleteElement(head,1);
}

void * thread3(void * args)
{
	node_t * head = (node_t *)args;
	insert(10,head);
	insert(8,head);
	insert(33,head);
	//deleteElement(head,0);
}
void * thread4(void * args)
{
	node_t * head = (node_t *)args;
	insert(6,head);
	insert(4,head);
	insert(23,head);
	//deleteElement(head,0);
}
void * thread5(void * args)
{
	node_t * head = (node_t *)args;
	insert(2,head);
	insert(0,head);
	insert(13,head);
	//deleteElement(head,0);
}
void * thread6(void * args)
{
	node_t * head = (node_t *)args;
	insert(20,head);
	insert(22,head);
	insert(3,head);
	//deleteElement(head,0);
}
void * thread7(void * args)
{
	node_t * head = (node_t *)args;
	insert(120,head);
	insert(122,head);
	insert(113,head);
	//deleteElement(head,0);
}

void * thread8(void * args)
{
	node_t * head = (node_t *)args;
	insert(201,head);
	insert(221,head);
	insert(31,head);
	//deleteElement(head,1);
}

void * thread9(void * args)
{
	node_t * head = (node_t *)args;
	insert(9,head);
	insert(19,head);
	insert(29,head);
	//deleteElement(head,0);
}
void * thread10(void * args)
{
	node_t * head = (node_t *)args;
	insert(39,head);
	insert(49,head);
	insert(59,head);
	//deleteElement(head,0);
}
void * thread11(void * args)
{
	node_t * head = (node_t *)args;
	insert(69,head);
	insert(79,head);
	insert(89,head);
	//deleteElement(head,0);
}
void * thread12(void * args)
{
	node_t * head = (node_t *)args;
	insert(99,head);
	insert(109,head);
	insert(119,head);
	//deleteElement(head,0);
}
void * thread13(void * args)
{
	node_t * head = (node_t *)args;
	insert(129,head);
	insert(139,head);
	insert(149,head);
	//deleteElement(head,0);
}
void * thread14(void * args)
{
	node_t * head = (node_t *)args;
	insert(159,head);
	insert(169,head);
	insert(179,head);
	//deleteElement(head,0);
}
void * thread15(void * args)
{
	node_t * head = (node_t *)args;
	insert(189,head);
	insert(199,head);
	insert(209,head);
	//deleteElement(head,0);
}
void * thread16(void * args)
{
	node_t * head = (node_t *)args;
	insert(219,head);
	insert(229,head);
	insert(239,head);
	//deleteElement(head,0);
}
void * thread17(void * args)
{
	node_t * head = (node_t *)args;
	insert(200,head);
	insert(190,head);
	insert(180,head);
	//deleteElement(head,0);
}
void * thread18(void * args)
{
	node_t * head = (node_t *)args;
	insert(170,head);
	insert(160,head);
	insert(150,head);
	//deleteElement(head,0);
}
void * thread19(void * args)
{
	node_t * head = (node_t *)args;
	insert(140,head);
	insert(130,head);
	insert(135,head);
	//deleteElement(head,0);
}
void * thread20(void * args)
{
	node_t * head = (node_t *)args;
	insert(145,head);
	insert(155,head);
	insert(165,head);
	//deleteElement(head,0);
}
