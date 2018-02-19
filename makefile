CC = gcc

memgrindmake: memgrind.c mymalloc.c
	$(CC) -o memgrindmake memgrind.c mymalloc.c

clean:
		rm memgrindmake
