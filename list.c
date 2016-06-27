/*
 * list.c
 *
 *  Created on: Jun 26, 2016
 *      Author: sumant
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>

#define EPSILON 0.2

typedef struct node
{
	int data;
	struct node * next;
	struct node * backlink;
}node_lf;

struct list
{
	node_lf * head;
	node_lf * (*init)();
	int (*insert)(int k,node_lf* head);
	int (*delete)(int,node_lf *);
	void (*print)(node_lf *);
	void (*destructor)(node_lf *);
};
typedef struct list * List;
typedef struct searchfrom
{
	node_lf * current;
	node_lf * next;
}return_sf;

typedef struct csArg
{
	int * node;
}cs_arg;

typedef struct return_tryFlag
{
	node_lf * node;
	int result;
}return_tf;

void HelpFlagged(node_lf * prev, node_lf * del_node);

node_lf * setMark(node_lf * p)
{
    return (node_lf *)((uintptr_t)p | 2);
}

node_lf * setFlag(node_lf * p)
{
    return (node_lf *)((uintptr_t)p | 1);
}

node_lf * clrMark(node_lf * p)
{
    return (node_lf *)((uintptr_t)p & 0xFFFFFFFD);
}

node_lf * clrFlag(node_lf * p)
{
    return (node_lf *)((uintptr_t)p & 0xFFFFFFFE);
}

node_lf * clrAll(node_lf * p)
{
	return (node_lf * )((uintptr_t)p & 0xFFFFFFFC);
}

int getMark(node_lf * p)
{

	int r = (int)((uintptr_t)p & 0x00000002);
	if(r == 2)
		return 1;
	return r;
}

int getFlag(node_lf * p)
{
	return (int)((uintptr_t)p & 0x00000001);
}

node_lf * getNodeAddress(node_lf * p)
{
	return (node_lf * )((uintptr_t)p & 0xFFFFFFFC);
}


node_lf * constructArgs(node_lf * node, int mark, int flag)
{
	node_lf * temp = getNodeAddress(node);
	if(mark == 1)
		(temp) = setMark(temp);
	if(flag == 1)
		(temp) = setFlag(temp);
	return temp;
}

void HelpMarked(node_lf * prev, node_lf * del_node)
{
	node_lf * next = getNodeAddress(del_node)->next;

	node_lf * del = constructArgs(del_node,0,1);
	node_lf * next_node = constructArgs(next,0,0);

	__sync_val_compare_and_swap ((unsigned int *)&(getNodeAddress(prev)->next), (unsigned int)del, (unsigned int)next_node);

	free(getNodeAddress(del_node));

}

return_sf * SearchFrom(int k,node_lf * curr)
{
	return_sf *s = (return_sf *)malloc(sizeof(return_sf));
	node_lf * next = curr->next;
	while(getNodeAddress(next)->data <= k)
	{
		while(getMark(next) == 1 && (getMark(curr) == 0 || getNodeAddress(curr)->next != getNodeAddress(next)))
		{
			if(getNodeAddress(curr)->next == getNodeAddress(next))
			{
				HelpMarked(curr,next);
			}
			next = getNodeAddress(curr)->next;
		}
		if(getNodeAddress(next)->data <= k)
		{
			curr = next;
			next = getNodeAddress(curr)->next;
		}

	}
	s->current = curr;
	s->next = next;
	return s;
}

void TryMark(node_lf * del_node)
{
	node_lf * next;
	node_lf * result;
	do
	{
		next = getNodeAddress(del_node)->next;

		node_lf * next_node = constructArgs(next,0,0);
		node_lf * next_node1 = constructArgs(next,1,0);

		result = (node_lf *)__sync_val_compare_and_swap((unsigned int *)&(getNodeAddress(del_node)->next),
														(unsigned int)(next_node),(unsigned int)(next_node1));

		if(getMark(result) == 0 && getFlag(result) == 1)
			HelpFlagged(del_node,result);
	}while(getMark(getNodeAddress(del_node)->next) != 1);
}

void HelpFlagged(node_lf * prev, node_lf * del_node)
{
	getNodeAddress(del_node)->backlink = prev;
	if(getMark(getNodeAddress(del_node)->next) == 0)
		TryMark(del_node);
	HelpMarked(prev,del_node);
}

int insert(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k,head);
	node_lf * prev;
	node_lf * next;
	node_lf * prev_succ = (node_lf *)malloc(sizeof(node_lf));
	prev = s->current;
	next = s->next;
	free(s);
	if(getNodeAddress(prev)->data == k)
		return -1;
	node_lf * newNode = (node_lf *)malloc(sizeof(node_lf));
	newNode->data = k;
	while(1)
	{
		prev_succ->next = getNodeAddress(prev)->next;
		if(getFlag(prev_succ) == 1)
			HelpFlagged(prev,getNodeAddress(prev_succ)->next);
		else
		{
			newNode->next = next;

			node_lf * next_node = constructArgs(next,0,0);
			node_lf * new_Node = constructArgs(newNode,0,0);

			node_lf * result = (node_lf *)__sync_val_compare_and_swap((unsigned int *)&(getNodeAddress(prev)->next),
																		(unsigned int)(next_node),(unsigned int)(new_Node));

			if(result == next)// || next == NULL)
			{
				return 0;
			}
			else
			{
				if(getFlag(result) == 1)
					HelpFlagged(prev,(result)->next);
				while(getMark(prev) == 1)
					prev = getNodeAddress(prev)->backlink;
			}

		}
		s = SearchFrom(k,prev);
		if(getNodeAddress(s->current)->data == k)
		{
			free(newNode);
			free(s);
			return -1;
		}
	}
	free(s);
	free(prev_succ);
	//return 0;
}

return_tf * TryFlag(node_lf * prev, node_lf * target)
{
	return_tf * r = (return_tf *)malloc(sizeof(return_tf));
	while(1)
	{
		if(getNodeAddress(prev)->next == target && getMark(getNodeAddress(prev)->next) == 0 && getFlag(getNodeAddress(prev)->next) == 1) // Already Flagged. Some other process would delete it.
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		node_lf * target_node = constructArgs(target,0,0);
		node_lf * target_node_new = constructArgs(target,0,1);

		node_lf * result = (node_lf *)__sync_val_compare_and_swap((unsigned int *)&(getNodeAddress(prev)->next),
																	(unsigned int)(target_node),(unsigned int)(target_node_new));
		if(result == target && getMark(result) == 0 && getFlag(result) == 0)
		{
			r->node = prev;
			r->result = 1;
			return r;
		}
		if(result == target && getMark(result) == 0 && getFlag(result) == 1)
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		while(getMark(getNodeAddress(prev)->next) == 1)
			prev = getNodeAddress(prev)->backlink;
	}
	return_sf * s = SearchFrom((getNodeAddress(target)->data) - EPSILON,  prev);
	if(s->next != target)
	{
		r->node = NULL;
		r->result = 0;
		free(s);
		return r;
	}
	free(s);
}

int delete_node(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k - EPSILON,head);
	node_lf * prev = s->current;
	node_lf * del = s->next;
	free(s);
	if(getNodeAddress(del)->data != k)
		return -1;
	return_tf * tf = TryFlag(prev, del);
	prev = tf->node;
	if(prev != NULL)
		HelpFlagged(prev, del);
	if(tf->result == 0)
	{
		free(tf);
		return -1;
	}
	free(tf);
	return 1;
}

node_lf * init_LF_list()
{
	node_lf * head = (node_lf *)malloc(sizeof(node_lf));
	node_lf * tail = (node_lf *)malloc(sizeof(node_lf));
	head->next = tail;
	head->data = -10000;
	tail->next = NULL;
	tail->data = 10000;
	return head;
}

void printlist(node_lf * head)
{
	head = getNodeAddress(head)->next;
	while(getNodeAddress(head)->data != 10000)
	{
		printf("\t%d",getNodeAddress(head)->data);
		head = head->next;
	}
}

void destroy(node_lf * head)
{
	node_lf * next;
	node_lf * curr = getNodeAddress(head);
	while(getNodeAddress(curr) != 0)
	{
		next = getNodeAddress(curr)->next;
		free(curr);
		curr = next;
	}
}

List list_init()
{
	List temp = (List)malloc(sizeof(struct list));
	temp->init = init_LF_list;
	temp->delete = delete_node;
	temp->insert = insert;
	temp->print = printlist;
	temp->destructor = destroy;
	return temp;
}

void *thread1(void *);
void *thread2(void *);

int main()
{
	List mylist = list_init(); //initialize the list object. Can be called as constructor
	mylist->head = mylist->init(); //initialize the list;
	mylist->insert(12,mylist->head);
	mylist->insert(14,mylist->head);
	mylist->insert(22,mylist->head);
	mylist->insert(24,mylist->head);
	pthread_t t1,t2;
	pthread_create (&t2, NULL, thread2, (void *)mylist);
	pthread_create (&t1, NULL, thread1, (void *)mylist);
	pthread_join (t1, NULL);
	pthread_join (t2, NULL);
	mylist->print(mylist->head);
	mylist->destructor(mylist->head);
	return 0;
}

void * thread1(void * args)
{
	List list = (List)args;
	sleep(1);
	list->delete(12,list->head);
	list->insert(12,list->head);
	list->insert(16,list->head);
}

void * thread2(void * args)
{
	List list = (List)args;
	sleep(2);
	list->delete(12,list->head);
	list->delete(24,list->head);
	//insert(12,head);
}


