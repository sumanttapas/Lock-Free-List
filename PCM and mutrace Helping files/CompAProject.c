#include <stdio.h>
#include <stdlib.h>
#define SIZE 2 
int main()
{
	int row, column, k, sum = 0;
	int first[SIZE][SIZE], second[SIZE][SIZE], multiply[SIZE][SIZE];

	
	
 
	for (row = 0; row < SIZE; row++)
	    for (column = 0; column < SIZE; column++)
			//scanf("%d", &first[row][column]);
	    	first[row][column] = ((rand())%1000);
 
	for (row = 0; row < SIZE; row++) 
	{
		for (column = 0; column < SIZE; column++)
			printf("%d\t", first[row][column]);

		printf("\n");
	}
 
  printf("\n");
printf("\n");
printf("\n");

   
 
    for (row = 0; row < SIZE; row++)
		for (column = 0; column < SIZE; column++)
			//scanf("%d", &second[row][column]);
	        second[row][column] = ((rand())%1000);
	for (row = 0; row < SIZE; row++) 
	{
		for (column = 0; column < SIZE; column++)
			printf("%d\t", second[row][column]);

		printf("\n");
	}
    for (row = 0; row < SIZE; row++) 
	{
		for (column = 0; column < SIZE; column++) 
		{
			sum = 0;	        
			for (k = 0; k < SIZE; k++) 
			{
	          sum = sum + first[row][k]*second[k][column];
	        }
 
    	    multiply[row][column] = sum;
    	    
		}
	}
	printf("\n");
	printf("\n");
	printf("Product of entered matrices:-\n");
 
	for (row = 0; row < SIZE; row++) 
	{
		for (column = 0; column < SIZE; column++)
    		printf("%d\t", multiply[row][column]);

  		printf("\n");
	}
	
 
	return 0;
}
