#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.c"
int main()
{
    int i;
    for (i = 0; i < 150;i++)
    {
    void * p = my_malloc(1);
    my_free(p);
    }
    char * ptrs[150];
    for(i = 0; i < 50;i++)
    {
        ptrs[i] = my_malloc(1);
    }
    for(i = 0;i < 50;i++)
    {
        my_free(ptrs[i]);
    }
    for(i = 0; i < 50;i++)
    int counter = 0;
    while(c < 150)
    {
        int r = rand()%2;

        if (r)
        {
            counter++;
            ptrs[rand()%150] = my_malloc()
        }
    }
}

