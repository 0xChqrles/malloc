/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:36:00 by clanier           #+#    #+#             */
/*   Updated: 2017/09/23 21:58:35 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <err.h>

void	getPageMultiple(size_t size)
{
	size_t	multiple;
	int		pageSize;

	pageSize = getpagesize();
	multiple = 100;
	while (multiple * size % pageSize)
		multiple++;
	return (multiple);
}

void	initZone(void **page, size_t pageSize, size_t size)
{
	if (!(*page) || sizeof(*page) < size)
	{
		if (*page)
			free(*page);
		*page = allocMem(size * getPageMultiple(size));
	}
	return (/* fonction qui va juste decouper et te renvoyer ce dont t'as besoin */);
}

void	*malloc(size_t size)
{
	static void	*tiny;
	static void	*small;

	if (size > SMALL)
		return (allocMem(size));
	if (size <= TINY)
		return (initZone(&tiny, TINY, size));
	else
		return (initZone(&small, SMALL, size));
}

void	*allocMem(size_t size)
{
	void	*ptr;

	if (size <= 0)
		return (NULL);
	ptr = mmap (0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	return (ptr);
}
