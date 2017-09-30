/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:36:00 by clanier           #+#    #+#             */
/*   Updated: 2017/10/01 00:06:16 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <err.h>

t_line	line = {NULL, NULL, NULL, 0};

void	*initMalloc(size_t size, void **page)
{
	t_malloc	*head;

	head = (t_malloc*)(*page + size);
	head->size = size - sizeof(t_page) - sizeof(t_malloc);
	head->prev = NULL;
	head->next = NULL;
	head->isFree = true;
	return (head);
}

void	*initPage(size_t size, void **page, void *prev)
{
	t_page	*head;

	head = (t_map*)(*page);
	head->first = initMalloc(size, *page);
	head->prev = prev;
	head->next = NULL;
	head->size = size;
	head->end = *page + size - 1;
	if (prev)
		prev->next = head;
	return (head);
}

int		createMap(size_t allocMax, void	**page, void *prev)
{
	size_t	size;
	size_t	pageSize;

	pageSize = getpagesize();
	size = 100 * (allocMax + sizeof(t_malloc)) + sizeof(t_page);
	if (size % pageSize)
		size += pageSize - size % pageSize;
	if (size > line.limit)
		return (-1);
	if ((*page = mmap(0, size, MMAP_PROT, MAP_FLAGS, -1, 0)) == MMAP_FAILED)
		return (-1);
	line.limit -= size;
	initMap(size, page, prev);
}

int		init()
{
	struct rlimit	limit;

	if (!getrlimit(RLIMIT_MEMLOCK, &limit))
		line.limit = limit.rlim_cur;
	if (createPage(TINY, &line.tiny, NULL) < 0)
		return (-1);
	if (createPage(SMALL, &line.small, NULL) < 0)
		return (-1);
	return (0);
	i =
}

void	*setMalloc(size_t size, t_malloc **mem)
{
	t_malloc	*new;

	new = (void*)mem + sizeof(t_malloc) + size;
	new->size = mem->size - size - sizeof(t_malloc);
	new->isFree = true;
	new->next = mem->next;
	new->prev = *mem;
	(*mem)->next = new;
	(*mem)->isfree = false;
	(*mem)->size = size;
	return ((*mem) + sizeof(t_malloc));
}

void	*searchMemory(size_t size, void **page, size_t sizeMax)
{
	t_malloc	*mtmp;
	t_page		*ptmp;

	ptmp = (t_page*)(*page);
	while (ptmp)
	{
		mtmp = ptmp->first;
		while (mtmp)
		{
			if (mtmp->isfree && mtmp->size > size + sizeof(t_malloc))
				return (setMalloc(size, &mtmp));
			else if (mtmp->isFree && mtmp->size >= size)
			{
				mtmp->isFree = false;
				return ((void*)mtmp + sizeof(t_malloc));
			}
			mtmp = mtmp->next;
		}
	}
	if (createPage(SMALL, page, *page) < 0)
		return (NULL);
	ptmp = (t_page*)(*page);
	mtmp = ptmp->first;
	return (setMalloc(size, &mtmp));
}

void	*largeMalloc(size_t size)
{
	void		*ptr;
	t_malloc	*tmp;
	t_malloc	*new;

	size += sizeof(t_malloc);
	if (line.limit < size
	|| (ptr = mmap(0, size, MMAP_PROT, MAP_FLAGS, -1, 0)) == MMAP_FAILED)
		return (NULL);
	line.limit -= size;
	new = (*t_malloc)ptr;
	new->next = NULL;
	new->prev = NULL;
	new->isFree = false;
	new->isFree = size - sizeof(t_malloc);
	if (!line.large)
		line.large = new;
	else
	{
		tmp = line.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (ptr + sizeof(t_malloc));
}

void	*malloc(size_t size)
{
	if ((!line.tiny && init() < 0) || size <= 0)
		return (NULL);
	if (size < TINY)
		return (searchMemory(size, &line.tiny, TINY));
	if (size < SMALL)
		return (searchMemory(size, &line.small, SMALL));
	largeMalloc(size, &line.large);
}
