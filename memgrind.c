#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
int main()
{
	int * arr = (int*)my_malloc(1000);
	int i;
	for (i = 0; i <5;i++)
    {
        arr[i] = i;
        printf("arr[%d] = %d\n", arr[i], i);
    }
    int * hi = (int*)my_malloc(2500);
    for (i = 0; i <50;i++)
    {
        hi[i] = 2*i;
        printf("hi[%d] = %d\n", i, hi[i]);
    }
    my_free(hi);
    char  * cool = (char*)my_malloc(2500);
    cool = "hello";
    puts(cool);
}
