/*
 * list.c
 *
 *  Created on: May 30, 2016
 *      Author: Sumant
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <stdatomic.h>

#define EPSILON 0.2
#define LOCK_PREFIX "lock ; "


typedef struct node
{
	int data;
	struct node * next;
	struct node * backlink;
}node_lf;

typedef struct searchfrom
{
	node_lf * current;
	node_lf * next;
}return_sf;

typedef struct csArg
{
	node_lf * node;
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
	return (int)((uintptr_t)p & 0x00000002);
}

int getFlag(node_lf * p)
{
	return (int)((uintptr_t)p & 0x00000001);
}

node_lf * getNodeAddress(node_lf * p)
{
	return (node_lf * )((uintptr_t)p & 0xFFFFFFFC);
}

static inline node_lf* cs(cs_arg * address, cs_arg *old_val, cs_arg *new_val)
{
	node_lf * value;
	__asm__ __volatile__("lock cmpxchg8b %1; "
				:"=q"(value)
				:"m"(address->node->next), "a"(old_val->node), "c"(new_val->node)
				:"memory");
	return value;
}
/*static inline node_lf cs(node_lf * address, cs_arg *old_val, cs_arg *new_val)
{
	node_lf value;
	//int ret =5,old = 5,new =5;
	int  ptr;

	 __asm__ __volatiljunk `4(%ecx)' after registere__(LOCK_PREFIX "cmpxchgw %1,%2"
	                 : "=a"(value)
	                 : "q"(new), "m"(*address), "0"(old)
	                 : "memory");
	//value = (node_lf )ptr;
	return value;
}*/

/*node_lf *cs (cs_arg * address, cs_arg *old_val, cs_arg *new_val )
{
	node_lf *value = (address->node)->next;
	if ((address->node->next) == old_val->node)
	{
		(address->node)->next = new_val->node;
	}
	return value;
}*/


cs_arg * constructArgs(node_lf * node, int mark, int flag)
{
	cs_arg * args = malloc(sizeof(cs_arg));
	args->node=getNodeAddress(node);
	if(mark == 1)
		args->node = setMark(args->node);
	if(flag == 1)
		args->node = setFlag(args->node);
	return args;
}

void HelpMarked(node_lf * prev, node_lf * del_node)
{
	node_lf * next = getNodeAddress(del_node)->next;
	cs_arg * del = constructArgs(del_node,0,1);
	cs_arg * ne = constructArgs(next,0,0);
	cs_arg * prev1 = constructArgs(prev->next,getMark(prev),getFlag(prev));
	cs(prev1, del, ne);
	free(del_node);

}

return_sf * SearchFrom(int k,node_lf * curr)
{
	return_sf *s = malloc(sizeof(return_sf));
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
		cs_arg * ne = constructArgs(next,0,0);
		cs_arg * ne1 = constructArgs(next,1,0);
		cs_arg * prev1 = constructArgs(getNodeAddress(del_node)->next,getMark(del_node),getFlag(del_node));
		result = cs(prev1,ne,ne1);
		if(getMark(result) == 0 && getFlag(result) == 1)
			HelpFlagged(del_node,result);
	}while(getMark(del_node) != 1);
}

void HelpFlagged(node_lf * prev, node_lf * del_node)
{
	getNodeAddress(del_node)->backlink = prev;
	if(getMark(del_node) == 0)
		TryMark(del_node);
	HelpMarked(prev,del_node);
}



int insert(int k, node_lf * head)
{
	return_sf * s = SearchFrom(k,head);
	node_lf * prev;
	node_lf * next;
	node_lf * prev_succ = malloc(sizeof(node_lf));
	prev = s->current;
	next = s->next;
	if(getNodeAddress(prev)->data == k)
		return -1;
	node_lf * newNode = malloc(sizeof(node_lf));
	newNode->data = k;
	while(1)
	{
		prev_succ->next = getNodeAddress(prev)->next;
		if(getFlag(prev_succ) == 1)
			HelpFlagged(prev,getNodeAddress(prev_succ)->next);
		else
		{
			newNode->next = next;
			cs_arg * ne = constructArgs(next,0,0);
			cs_arg * new = constructArgs(newNode,0,0);
			cs_arg * prev1 = constructArgs(getNodeAddress(prev),getMark(prev),getFlag(prev));
			node_lf * result = cs(prev1,ne,new);

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
			return -1;
		}
	}
	//return 0;
}
/*
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
		cs_arg * prev1 = constructArgs(prev->next,prev->mark,prev->flag);
		cs_arg result = cs(prev1, ne, ne1);
		if(result.node == target && result.mark == 0)// && result.flag == 0)
		{
			r->node = prev;
			r->result = 1;
			return r;
		}
		if(result.node == target && result.mark == 0)// && result.flag == 1)
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
*/
/*int delete(int k, node_lf * head)
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
}*/

node_lf * init_LF_list()
{
	node_lf * head = malloc(sizeof(node_lf));
	node_lf * tail = malloc(sizeof(node_lf));
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

int main()
{
	node_lf * head = init_LF_list();
	//return_sf * s = SearchFrom(1,head);
	insert(1,head);
	//printlist(head);
	insert(2,head);
	insert(3,head);
	insert(4,head);
	printlist(head);
	printf("\n");
	//delete(1,head);
	//printlist(head);
	return 0;
}

