#include "mymalloc.h"
#include <ctype.h>
static char myblock[5000];
void * mymalloc(int size);
int findIndex(int size);

int main()
{
	mymalloc(5);
}
char * mymalloc(int size)
{
	if (size == 0)
		return 
	for(i = 0; i <5000; i++)
	{
		if (isdigit(myblock[i]))//if header byte found
		{
			i = i + myblock[i];	//jump past reserved bytes
			if(i > 5000)return -1;//if jump is out of bounds return error
			continue;
		}
		else
		{
			if((i + size) > 5000)return -1;//if index found but requested memory is out of bounds
			myblock[i] = size;
		}
	}
	return *myblock[i]; 
}
