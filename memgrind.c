#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
int main()
{
    int i;
	for(i = 0; i < 150; i++)
    {
        char * byte = (char *)my_malloc(1);
        free(byte);
    }
    char * ptrs[150];
    for(i = 0; i < 150;i++)
    {
        ptrs[i] = my_malloc(1);
    }
    for(i = 0;i < 150;i++)
    {
        my_free(ptrs[i]);
    }


}
