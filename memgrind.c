#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"
int main()
{
    //Workload A: Malloc() 1 byte and immediately free it x150
    
    int i;
   for (i = 0; i < 150;i++)
    {
    void * p = my_malloc(1);
    my_free(p);
    }

    //Workload B: Malloc(), store pointer in arrayx150 times
    
    char * ptrs[150];
    for(i = 0; i < 150;i++)
    {
        ptrs[i] = my_malloc(1);
    }
    for(i = 0;i < 150;i++)
    {
        my_free(ptrs[i]);
    }
    
    //Workload C: Randomly choose b/w 1 byte malloc and 1 byte free, continue until 150 mallocs
    
 int mallocCounter = 0;  //counts total number of mallocs
    int pointersMalloc = 0; //counts pointers currently malloc
    char*p = NULL;
    while(mallocCounter <= 150){
        if(pointersMalloc == 0){ //if no byte has been allocated, then first malloc
            p = my_malloc(1);
            mallocCounter++;
            pointersMalloc++;
        }
        int r = rand()%2;
        if(r==1){           //if r = 1 malloc 1 byte
           p = my_malloc(1);
            mallocCounter++;
            pointersMalloc++;
        }else{
            my_free(p);     //if r=0 free byte
            pointersMalloc--;
        }
    }
    while(pointersMalloc!=0){  // after 150 mallocs, free
        my_free(p);
        pointersMalloc--;
    }
    
    //Workload D: Randomly-sized malloc() or free() pointers
    
   
}


