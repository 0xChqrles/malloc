#include "malloc.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	char	*win;
	char	*combo;

	if (!(win = (char*)malloc(sizeof(char) * 4)))
	{
		printf("Error\n");
		return (0);
	}
	if (!(combo = (char*)malloc(sizeof(char) * 6)))
	{
		printf("Error\n");
		return (0);
	}
	strcpy(win, "win");
	strcpy(combo, "combo");
	printf("%s\n", win);
	printf("%s\n", combo);
}
