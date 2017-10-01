/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:28:45 by clanier           #+#    #+#             */
/*   Updated: 2017/10/01 21:09:30 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	freeMemory(t_malloc *mem)
{
	if (mem->prev && mem->prev->isFree)
	{
		mem->prev->size += mem->size + sizeof(t_malloc);
		mem->prev->next = mem->next;
		if (mem->next)
			mem->next->prev = mem->prev;
	}
	if (mem->next && mem->next->isFree)
	{
		mem->size += mem->next->size + sizeof(t_malloc);
		if (mem->next->next)
			mem->next->next->prev = mem;
		mem->next = mem->next->next;
		mem->isFree = true;
	}
}

void	freePage(t_page *page, char pageType)
{
	t_malloc	*mtmp;

	mtmp = page->first;
	while (mtmp)
	{
		if (!mtmp->isFree)
			return ;
		mtmp = mtmp->next;
	}
	if (page->prev)
		page->prev->next = page->next;
	else if (pageType == 't')
		line.tiny = page->next;
	else if (pageType == 's')
		line.small = page->next;
	if (page->next)
		page->next->prev = page->prev;
	munmap((void*)page, page->size);
	page = NULL;
}

int		findPointer(void *ptr, void **page)
{
	t_page		*ptmp;
	t_malloc	*mtmp;

	ptmp = (t_page*)*page;
	while (ptmp)
	{
		if (ptr > (void*)ptmp && ptr < ptmp->end)
		{
			mtmp = ptmp->first;
			while (mtmp && ptr != mtmp + sizeof(t_malloc))
				mtmp = mtmp->next;
			if (mtmp && ptr == mtmp + sizeof(t_malloc))
				return (mtmp);
			else
				return (NULL);
		}
		ptmp = ptmp->next;
	}
	return (NULL);
}

void	freeMemory(t_malloc *mem, char pageType)
{
	freeMemory(mem);
	freePage(mem, pageType);
}

void	free(void *ptr)
{
	t_malloc	*mtmp;

	if (!ptr)
	   return ;
	if (mtmp = findPointer(ptr, &line.tiny))
		return (freeMemory(mtmp, 't'))
	if (mtmp = findPointer(ptr, &line.small))
		return (freeMemory(mtmp, 's'));
	mtmp = line.large;
	while (mtmp && ptr != mtmp + sizeof(t_malloc))
		mtmp = mtmp->next;
	if (mtmp && ptr == mtmp + sizeof(t_malloc))
	{
		if (mtmp->prev)
			mtmp->prev->next = mtmp->next;
		else
			line.large = mtmp->next;
		if (mtmp->next)
			mtmp->next->prev = mtmp->prev;
		munmap(mtmp, mtmp->size + sizeof(t_malloc));
	}
}
