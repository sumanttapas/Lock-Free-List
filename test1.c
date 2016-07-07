#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static inline int
cas(volatile int* ptr, int old, int _new)
{
    int prev=0;
    __asm__ __volatile("lock cmpxchg8b %[ptr]\n\t"
                : [ptr] "+m" (*ptr), [prev] "=q" (prev),"+d" (old)
                 : "c" (_new)
		 : "cc", "memory"
                 );
    return *ptr;
}

int main()
{
 	int a=0;
	int b=3,c;
	//a=&b;
        c=cas(&a,0,1);
	printf("c=%d\n",c);
	printf("a=%d\n",a);
	return 0;
}
