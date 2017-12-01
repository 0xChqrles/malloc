#include "malloc.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	char	*win;
	char	*win2;

	malloc(20);
	win = malloc(120);
	malloc(20);
	realloc(win, 20);
	malloc(68);
	win2 = malloc(4100);
	win = malloc(5683);
	free(win);
	realloc(win2, 10);
	win = malloc(3000);
	win2 = malloc(3200);
	realloc(win, 1);
	show_alloc_mem();
}
