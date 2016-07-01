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


typedef struct node
{
	int data;
	struct node* next;
}node_t;

int c=0;

void *thread1(void *);
void *thread2(void *);

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
		node_t * n = malloc(sizeof(struct node));
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
		printf("\t%d",head->data);
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
	node_t * head = malloc(sizeof(node_t));
	head->next = NULL;
	return head;
}

int main(void)
{
	node_t * head = init_list();

	pthread_t t1,t2;
	pthread_create (&t2, NULL, thread2, (void *)head);
	pthread_create (&t1, NULL, thread1, (void *)head);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	printlist(head);
	return 0;
}

void * thread1(void * args)
{
	node_t * head = args;
	insert(12,head);
	insert(14,head);
	deleteElement(head,0);
}

void * thread2(void * args)
{
	node_t * head = args;
	insert(22,head);
	insert(24,head);
	deleteElement(head,1);
}
