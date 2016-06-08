/*
 * list.c
 *
 *  Created on: May 30, 2016
 *      Author: Sumant
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>

#define EPSILON 0.2

typedef struct node
{
	int data;
	struct node * next;
	struct node * backlink;
	int flag;
	int mark;
}node_lf;

typedef struct searchfrom
{
	node_lf * current;
	node_lf * next;
}return_sf;

typedef struct csArg
{
	node_lf * node;
	int mark;
	int flag;
}cs_arg;

typedef struct return_tryFlag
{
	node_lf * node;
	int result;
}return_tf;

static inline node_lf cs(node_lf * address, cs_arg *old_val, cs_arg *new_val)
{
  node_lf value = *address;
  __asm__ __volatile__("lock; cmpxchg16b %0; setz %1;":"=m"(*(volatile node_lf *)address),
		       "=q"(value)
		       :"m"(*(volatile node_lf *)address), "a"(old_val.mark), "d"(old_val.flag),
			"b"(new_val.mark), "c"(new_val.flag)
		       :"memory");
  return value;
}

void HelpFlagged(node_lf * prev, node_lf * del_node);
cs_arg * constructArgs(node_lf * node, int mark, int flag)
{
	cs_arg * args = malloc(sizeof(cs_arg));
	args->node=node;
	args->mark = mark;
	args->flag = flag;
	return args;
}

void HelpMarked(node_lf * prev, node_lf * del_node)
{
	node_lf * next = del_node->next;
	cs_arg * del = constructArgs(del_node,0,1);
	cs_arg * ne = constructArgs(next,0,0);
	cs(prev, del, ne);
	free(del_node);

}

return_sf * SearchFrom(int k,node_lf * curr)
{
	return_sf *s = malloc(sizeof(return_sf));
	node_lf * next = curr->next;
	while(next->data <= k)
	{
		while(next->mark == 1 && (curr->mark == 0 || curr->next != next))
		{
			if(curr->next == next)
			{
				HelpMarked(curr,next);
			}
			next = curr->next;
		}
		if(next->data <= k)
		{
			curr = next;
			next = curr->next;
		}

	}
	s->current = curr;
	s->next = next;
	return s;
}

void TryMark(node_lf * del_node)
{
	node_lf * next;
	node_lf result;
	do
	{
		next = del_node->next;
		cs_arg * ne = constructArgs(next,0,0);
		cs_arg * ne1 = constructArgs(next,1,0);
		result = cs(del_node,ne,ne1);
		if(result.mark == 0 && result.flag == 1)
			HelpFlagged(del_node,result.next);
	}while(del_node->mark != 1);
}

void HelpFlagged(node_lf * prev, node_lf * del_node)
{
	del_node->backlink = prev;
	if(del_node->mark == 0)
		TryMark(del_node);
	HelpMarked(prev,del_node);
}



int insert(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k,head);
	node_lf * prev;
	node_lf *next;
	node_lf *prev_succ = malloc(sizeof(node_lf));
	prev = s->current;
	next = s->next;
	if(prev->data == k)
		return -1;
	node_lf * newNode = malloc(sizeof(node_lf));
	newNode->data = k;
	while(1)
	{
		prev_succ->next = prev->next;
		prev_succ->mark = prev->mark;
		prev_succ->flag = prev->flag;
		if(prev_succ->flag == 1)
			HelpFlagged(prev,prev_succ->next);
		else
		{
			newNode->next = next;
			newNode->mark = 0;
			newNode->flag = 0;
			cs_arg * ne = constructArgs(next,0,0);
			cs_arg * new = constructArgs(newNode,0,0);
			node_lf result = cs(prev,ne,new);

			if(result.next == next)// || next == NULL)
			{
				return 0;
			}
			else
			{
				if(result.flag == 1)
					HelpFlagged(prev,result.next);
				while(prev->mark == 1)
					prev = prev->backlink;
			}

		}
		s = SearchFrom(k,prev);
		if(s->current->data == k)
		{
			free(newNode);
			return -1;
		}
	}
	//return 0;
}

return_tf * TryFlag(node_lf * prev, node_lf * target)
{
	return_tf * r = malloc(sizeof(return_tf));
	while(1)
	{
		if(prev->next == target && prev->mark == 0 && prev->flag == 1) // Already Flagged. Some other process would delete it.
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		cs_arg * ne = constructArgs(target,0,0);
		cs_arg * ne1 = constructArgs(target,0,1);
		node_lf result = cs(prev, ne, ne1);
		if(result.next == target && result.mark == 0 && result.flag == 0)
		{
			r->node = prev;
			r->result = 1;
			return r;
		}
		if(result.next == target && result.mark == 0 && result.flag == 1)
		{
			r->node = prev;
			r->result = 0;
			return r;
		}
		while(prev->mark == 1)
			prev = prev->backlink;
	}
	return_sf * s = SearchFrom(target->data - EPSILON,  prev);
	if(s->next != target)
	{
		r->node = NULL;
		r->result = 0;
		return r;
	}
}

int delete(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k - EPSILON,head);
	node_lf * prev = s->current;
	node_lf * del = s->next;
	if(del->data != k)
		return -1;
	return_tf * tf = TryFlag(prev, del);
	prev = tf->node;
	if(prev != NULL)
		HelpFlagged(prev, del);
	if(tf->result == 0)
		return -1;
	return 1;
}

node_lf * init_LF_list()
{
	node_lf * head = malloc(sizeof(node_lf));
	node_lf * tail = malloc(sizeof(node_lf));
	head->next = tail;
	head->mark = 0;
	head->flag = 0;
	head->data = -10000;
	tail->next = NULL;
	tail->mark = 0;
	tail->flag = 0;
	tail->data = 10000;
	return head;
}

void printlist(node_lf * head)
{
	head = head->next;
	while(head->data != 10000)
	{
		printf("\t%d\n",head->data);
		head = head->next;
	}
}

int main()
{
	node_lf * head = init_LF_list();
	insert(1,head);
	//printlist(head);
	insert(2,head);
	insert(3,head);
	insert(4,head);
	printlist(head);
	printf("\n");
	delete(1,head);
	printlist(head);
	return 0;
}

