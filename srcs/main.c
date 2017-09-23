#include "malloc.h"
#include <stdio.h>

int	main()
{
	char	*win;

	win = (char*)malloc(sizeof(char) * 4);
	win[0] = 'w';
	win[1] = 'i';
	win[2] = 'n';
	win[3] = '\0';
	printf("%s\n", win);
}
