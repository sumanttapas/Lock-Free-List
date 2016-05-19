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
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void insert(int data,node_t * head)
{
	node_t * last = head;
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
		pthread_mutex_lock(&mutex);
		last->next = n;
		n->next = NULL;
		pthread_mutex_unlock(&mutex);
	}
}

void printlist(node_t * head)
{
	do
	{
		printf("\t%d",head->data);
		head = head->next;
	}while(head != NULL);
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
	if(fork() == 0)
	{
		insert(13,head);
	}
	wait(NULL);
	insert(12,head);
	insert(14,head);

	printlist(head);
	return 0;
}
