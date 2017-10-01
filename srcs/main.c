#include "malloc.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	int		i = 0;
	char	*win;

	while (i++ < 10000)
	{
		if (!(win = (char*)malloc(sizeof(char) * 21000)))
		{
			printf("Error\n");
			return (0);
		}
		strcpy(win, "hey !!! It's working");
		printf("%d: %s\n", i, win);
		free(win);
	}
}
