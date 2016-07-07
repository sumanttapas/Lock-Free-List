/*
 ============================================================================
 Description : Linked list using locks
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
		node_t * n = malloc(sizeof(struct node));
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
		printf("\t%d",head->data);
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
	node_t * head = malloc(sizeof(node_t));
	node_t * tail = malloc(sizeof(node_t));
	head->next = tail;
	head->data = -10000;
	tail->data = 10000;
	return head;
}

int main(void)
{
	node_t * head = init_list();
	pthread_t t1,t2,t3,t4,t5,t6;
	pthread_create (&t2, NULL, thread2, (void *)head);
	pthread_create (&t1, NULL, thread1, (void *)head);
	pthread_create (&t3, NULL, thread3, (void *)head);
	pthread_create (&t4, NULL, thread4, (void *)head);
	pthread_create (&t5, NULL, thread5, (void *)head);
	pthread_create (&t6, NULL, thread6, (void *)head);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	pthread_join (t3, NULL);
	pthread_join (t4, NULL);
	pthread_join (t5, NULL);
	pthread_join (t6, NULL);
	printlist(head);
	return 0;
}

void * thread1(void * args)
{
	node_t * head = args;
	insert(12,head);
	insert(14,head);
	//deleteElement(head,0);
}

void * thread2(void * args)
{
	node_t * head = args;
	insert(22,head);
	insert(24,head);
	//deleteElement(head,1);
}

void * thread3(void * args)
{
	node_t * head = args;
	insert(32,head);
	insert(34,head);
	deleteElement(head,12);
	//deleteElement(head,0);
}
void * thread4(void * args)
{
	node_t * head = args;
	insert(42,head);
	insert(44,head);
	//deleteElement(head,0);
}
void * thread5(void * args)
{
	node_t * head = args;
	insert(52,head);
	insert(54,head);
	deleteElement(head,22);
	//deleteElement(head,0);
}
void * thread6(void * args)
{
	node_t * head = args;
	insert(62,head);
	insert(64,head);
	deleteElement(head,42);
	//deleteElement(head,0);
}
