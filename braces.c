/*
 * braces->c
 *
 *  Created on: May 19, 2016
 *      Author: sumant
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef struct stack_node
{
	char data[MAXSIZE];
	int top;
}snode_t;

char **braces(int value_size, char **values, int result_size);

void push(char c,snode_t * s)
{
	s->top += 1;
	if(s->top > MAXSIZE)
	{
		printf("Stack Overflow");
		return;
	}
	else
	{
		s->data[s->top] = c;
	}
}
char pop(snode_t * s)
{
	char r = s->data[s->top];
	if(s->top != 0)
		s->top -= 1;
	if(s->top < 0)
	{
		return -1;
	}
	return r;
}

snode_t * init_stack()
{
	snode_t * s = malloc(sizeof(struct stack_node));
	s->top=-1;
	return s;
}
int main()
{
	int numberOfTestCase,i;
	scanf("%d",&numberOfTestCase);
	getchar();

	char **values = (char **)malloc(numberOfTestCase*sizeof(char *));
	for(i=0;i<numberOfTestCase;i++)
	{
		values[i] = (char *)malloc(1000*sizeof(char));
	}
	//char values[numberOfTestCase][1000];
	for(i=0;i<numberOfTestCase;i++)
	{
		scanf("%s",values[i]);
	}
	char **res;
	res=braces(numberOfTestCase,values,numberOfTestCase);
	for(i=0;i<numberOfTestCase;i++)
	{
		puts(res[i]);
	}
	/*for (i = 0; i < numberOfTestCase; i++)
	{
	    char* currentIntPtr = values[i];
	    char* currentIntPtr1 = res[i];
	    free(currentIntPtr);
	    free(currentIntPtr1);
	}*/
	return 1;
}
char **braces(int value_size, char **values, int result_size)
{
	int i,j, flag = 1;

	char **res = (char **)malloc(result_size*sizeof(char *));
	for(i=0;i<value_size;i++)
	{
		res[i] = (char *)malloc(3*sizeof(char));
	}
	//char res[value_size][3];
	for(i=0;i<value_size;i++)
	{
		flag = 1;
		snode_t * s;
		if(i != 0)
			free(s);
		 s = init_stack();
		for(j=0;j<1000;j++)
		{
			if(values[i][j] == '{' || values[i][j] == '[' || values[i][j] == '(' )
				push(values[i][j],s);
			else if(values[i][j] == '}' || values[i][j] == ']' || values[i][j] == ')' )
			{
				char c = pop(s);
				if(c == -1)
				{
					flag = 0;
					break;
				}
				if(c == '{')
				{
					if(values[i][j] != '}')
						flag =0;
				}
				else if(c == '[')
				{
					if(values[i][j] != ']')
						flag =0;
				}
				else if(c == '(')
				{
					if(values[i][j] != ')')
						flag =0;
				}

			}

		}
		if(flag == 0)
		{
			res[i] = "NO";
		}
		else if(flag == 1 && s->top != 0 )
			res[i] = "NO";
		else
			res[i] = "YES";
	}

	return res;
}
