#include "malloc.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int	main()
{
	char	*win;
	char	*combo;

	printf("1 => %d\n", getpagesize());
	if (!(win = (char*)malloc(sizeof(char) * 4)))
	{
		printf("Error\n");
		return (0);
	}
	printf("2 => %d\n", getpagesize());
	if (!(combo = (char*)malloc(sizeof(char) * 6)))
	{
		printf("Error\n");
		return (0);
	}
	printf("3 => %d\n", getpagesize());
	strcpy(win, "win");
	strcpy(combo, "combo");
	printf("%s\n", win);
	printf("%s\n", combo);
}
