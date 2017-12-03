#include "includes/malloc.h"
#include <stdio.h>

int	main()
{
	char	*a = malloc(1);
	a[0] = 'm';
	printf("%s\n", a);
	free(a);
	printf("%s\n", a);
}
