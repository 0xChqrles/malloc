/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:36:00 by clanier           #+#    #+#             */
/*   Updated: 2017/12/01 21:14:56 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*initPage(size_t size, void **page, t_page *prev)
{
	t_malloc	*mhead;
	t_page		*phead;

	mhead = (t_malloc*)(*page + sizeof(t_page));
	mhead->size = size - sizeof(t_page) - sizeof(t_malloc) - 2;
	mhead->prev = NULL;
	mhead->next = NULL;
	mhead->isFree = true;
	phead = (t_page*)(*page);
	phead->first = mhead;
	phead->prev = prev;
	phead->next = NULL;
	phead->size = size;
	phead->end = *page + size - 1;
	if (prev)
		prev->next = *page;
	return (phead);
}

int		createPage(size_t allocMax, void **page, t_page *prev)
{
	size_t	size;
	size_t	pageSize;

	pageSize = getpagesize();
	size = 100 * (allocMax + sizeof(t_malloc)) + sizeof(t_page);
	if (size % pageSize)
		size += pageSize - size % pageSize;
	if (size > line.limit
	|| (*page = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0)) == MAP_FAILED)
		return (-1);
	line.limit -= size;
	initPage(size, page, prev);
	return (0);
}

int		init()
{
	struct rlimit	limit;

	if (!getrlimit(RLIMIT_MEMLOCK, &limit))
		line.limit = limit.rlim_cur;
	if ((!line.tiny && createPage(TINY, &line.tiny, NULL) < 0)
	|| (!line.small && createPage(SMALL, &line.small, NULL) < 0))
		return (-1);
	return (0);
}

void	*setMalloc(size_t size, t_malloc **mem)
{
	t_malloc	*new;

	new = *mem + sizeof(t_malloc) + size;
	new->size = (*mem)->size - size - sizeof(t_malloc) - 1;
	new->isFree = true;
	new->next = (*mem)->next;
	new->prev = *mem;
	(*mem)->next = new;
	(*mem)->isFree = false;
	(*mem)->size = size;
	return ((*mem) + sizeof(t_malloc));
}

void	*getFreeMemory(size_t size, void **page, size_t sizeMax)
{
	t_malloc	*mtmp;
	t_page		*ptmp;

	ptmp = (t_page*)(*page);
	while (ptmp)
	{
		mtmp = ptmp->first;
		while (mtmp)
		{
			if (mtmp->isFree && mtmp->size > size + sizeof(t_malloc))
				return (setMalloc(size, &mtmp));
			else if (mtmp->isFree && mtmp->size >= size)
			{
				mtmp->isFree = false;
				return (mtmp + sizeof(t_malloc));
			}
			mtmp = mtmp->next;
		}
		ptmp = (t_page*)ptmp->next;
	}
	if (createPage(sizeMax, page, *page) < 0)
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
	|| (ptr = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0)) == MAP_FAILED)
		return (NULL);
	line.limit -= size;
	new = (t_malloc*)ptr;
	new->next = NULL;
	new->prev = NULL;
	new->isFree = false;
	new->size = size - sizeof(t_malloc);
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
	return (new + sizeof(t_malloc));
}

void	*malloc(size_t size)
{
	if ((!line.tiny && init() < 0) || size <= 0)
		return (NULL);
	if (size < TINY)
		return (getFreeMemory(size, &line.tiny, TINY));
	if (size < SMALL)
		return (getFreeMemory(size, &line.small, SMALL));
	return (largeMalloc(size));
}
