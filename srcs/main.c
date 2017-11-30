#include "malloc.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	int		i = 0;
	char	*win;

	malloc(20);
	malloc(20);
	win = malloc(21);
	printf("3 = > %lu\n", (unsigned long)win);
	malloc(20);
	free(win);
	printf("2 = > %lu\n", (unsigned long)win);
	win = malloc(16);
	win = realloc(win, 20);
/*	while (i++ < 10000)
	{
		if (!(win = (char*)malloc(sizeof(char) * 210)))
		{
			printf("Error\n");
			return (0);
		}
		strcpy(win, "hey !!! It's working");
		printf("%d: %s\n", i, win);
		realloc(win, 10);
		free(win);
	}
	sleep(5);*/
}
