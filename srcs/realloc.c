/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:55:13 by clanier           #+#    #+#             */
/*   Updated: 2017/10/01 21:13:49 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	*reallocMemory(void *ptr, void **page, char pageType, size_t size)
{
	t_page		*ptmp;
	t_malloc	*mtmp;

	mtmp = (t_malloc*)ptr;
	ptmp = (t_page*)*page;
	(void)pageType;
	printf("hey");
	if (mtmp->size <= size)
		printf("nice job");
	return (NULL);
}

void	*moveData(t_malloc *src, void *dest, size_t size, bool free)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		if (i < src->size)
			((unsigned char*)(dest))[i] = ((unsigned char*)(src + sizeof(t_malloc)))[i];
		else
			((unsigned char*)(dest))[i] = 0;
		i++;
	}
	if (free)
		munmap(src, src->size + sizeof(t_malloc));
	return (dest);
}

void	*realloc(void *ptr, size_t size)
{
	t_malloc	*mtmp;
	void		*newLargePtr;

	if (!ptr)
		return (malloc(size));
	if ((mtmp = findPointer(ptr, &line.tiny)))
		return (reallocMemory(mtmp, &line.tiny, 't', size));
	if ((mtmp = findPointer(ptr, &line.small)))
		return (reallocMemory(mtmp, &line.small, 's', size));
	mtmp = line.large;
	while (mtmp && ptr != mtmp + sizeof(t_malloc))
		mtmp = mtmp->next;
	if (mtmp && ptr == mtmp + sizeof(t_malloc))
	{
		if (!(newLargePtr = malloc(size)))
			return (NULL);
		if (mtmp->prev)
			mtmp->prev->next = mtmp->next;
		else
			line.large = mtmp->next;
		if (mtmp->next)
			mtmp->next->prev = mtmp->prev;
		return (moveData(mtmp, newLargePtr, size, true));
	}
	return (NULL);
}
