#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
static inline unsigned long
cas(volatile unsigned long* ptr, unsigned long old, unsigned long _new)
{
    unsigned long prev=0;
    __asm__ __volatile("lock cmpxchg8b %0;"
                 : "=m"(prev)
                 : "m"(*ptr),"a"(old),"c"(_new)
                 );
    return prev;
}

int main()
{
	
	unsigned long *a;
	unsigned long b=5,c;
	a=&b;
        c=cas(a,b,6);
	printf("%lu\n",c);
	return 0;
}
	
