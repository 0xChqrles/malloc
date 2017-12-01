/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:55:13 by clanier           #+#    #+#             */
/*   Updated: 2017/12/01 21:26:19 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*moveData(t_malloc *src, void *dest, size_t size)
{
	unsigned int	i;

	i = 0;
	while (i < size && i < src->size)
	{
		((unsigned char*)(dest))[i] =
		((unsigned char*)(src + sizeof(t_malloc)))[i];
		i++;
	}
	return (dest);
}

void	*reallocMemory(void *ptr, size_t size, char pageType)
{
	t_malloc	*mtmp;
	void		*new;

	mtmp = (t_malloc*)ptr;
	if (size <= mtmp->size && (pageType == 't' || (pageType == 's' && size > TINY)))
	{
		if (mtmp->size > sizeof(t_malloc)
		&& size < mtmp->size - sizeof(t_malloc))
			return (setMalloc(size, &mtmp));
		else
			return (mtmp + sizeof(t_malloc));
	}
	if (!(new = malloc(size)))
		return (NULL);
	moveData(mtmp, new, size);
	free(mtmp + sizeof(t_malloc));
	return (new);
}

void	*realloc(void *ptr, size_t size)
{
	t_malloc	*mtmp;
	void		*new;

	if (!ptr)
		return (malloc(size));
	if ((mtmp = findPointer(ptr, &line.tiny)))
		return (reallocMemory(mtmp, size, 't'));
	if ((mtmp = findPointer(ptr, &line.small)))
		return (reallocMemory(mtmp, size, 's'));
	mtmp = line.large;
	while (mtmp && ptr != mtmp + sizeof(t_malloc))
		mtmp = mtmp->next;
	if (mtmp && ptr == mtmp + sizeof(t_malloc))
	{
		if (mtmp->size >= size && size > SMALL)
			return (ptr);
		if (!(new = malloc(size)))
			return (NULL);
		moveData(mtmp, new, size);
		free(ptr);
		return (new);
	}
	return (NULL);
}
