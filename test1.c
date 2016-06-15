#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static inline int
cas(volatile int* ptr, int old, int _new)
{
    int prev=0;
    __asm__ __volatile("lock cmpxchg8b %[ptr]\n\t"
                : [prev] "=q" (prev), [ptr] "+m" (*ptr),"+d" (old)
                 : "c" (_new)
                 );
    return prev;
}

int main()
{
	
	int *a;
	int b=3,c;
	a=&b;
        c=cas(a,b,6);
	printf("%d\n",c);
	return 0;
}
