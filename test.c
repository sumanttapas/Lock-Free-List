#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//#include <stdatomic.h>
typedef struct node
{
	int data;
	struct node * next;
	struct node * backlink;
	int flag;
	int mark;
}node_lf;

node_lf * setMark(node_lf * p)
{
    return (node_lf *) ((uintptr_t)p | 2);
}

node_lf * setFlag(node_lf * p)
{
    return (node_lf *) ((uintptr_t)p | 1);
}

node_lf * clrMark(node_lf * p)
{
    return (node_lf *) ((uintptr_t)p & 0xFFFFFFFD);
}

node_lf * clrFlag(node_lf * p)
{
    return (node_lf *) ((uintptr_t)p & 0xFFFFFFFE);
}

int main()
{
	int * p;
	int i =2;
	node_lf * head = malloc(sizeof(node_lf));
	node_lf * temp;
	head->data = 5;
	printf("\n%p",head);
	p = &i;
	//printf("%p",p);
	temp = setMark(head);
	printf("\n%p",temp);
	temp = setFlag(temp);
	printf("\n%p",temp);
	temp = clrFlag(temp);
	printf("\n%p",temp);
	temp = clrMark(temp);
	printf("\n%p",temp);
}
