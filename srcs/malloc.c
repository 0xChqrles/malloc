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

void	initZone(void **page, size_t pageSize)
{
	if (!(*page))
		*page = allocMem(size);
}

void	*malloc(size_t size)
{
	static void	*tiny;
	static void	*small;

	if (size <= TINY)
		initZone(&tiny, TINY);
	else if (size <= SMALL)
		initZone(&small, SMALL);
	else
		return (allocMem(size));
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
