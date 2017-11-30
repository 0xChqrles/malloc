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
#include <stdio.h>

void	freeMalloc(t_malloc *mem)
{
	mem->isFree = true;
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
	}
}

void	freePage(void **page, char pageType)
{
	t_page		*ptmp;
	t_malloc	*mtmp;

	ptmp = (t_page*)*page;
	if (!ptmp->prev && !ptmp->next)
		return ;
	mtmp = ptmp->first;
	while (mtmp)
	{
		if (!mtmp->isFree)
			return ;
		mtmp = mtmp->next;
	}
	if (ptmp->prev)
		ptmp->prev->next = ptmp->next;
	else if (pageType == 't')
		line.tiny = ptmp->next;
	else if (pageType == 's')
		line.small = ptmp->next;
	if (ptmp->next)
		ptmp->next->prev = ptmp->prev;
	munmap((void*)ptmp, ptmp->size);
	ptmp = NULL;
}

void		*findPointer(void *ptr, void **page)
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
			{printf("m => %lu\np => %lu\n", (unsigned long)mtmp, (unsigned long)ptr);
				mtmp = mtmp->next;}
			if (mtmp && ptr == mtmp + sizeof(t_malloc))
				return (mtmp);
			else
			{
				printf("oshit\n");
				return (NULL);
			}
		}
		ptmp = ptmp->next;
	}
	return (NULL);
}

void	freeMemory(t_malloc *mem, void **page, char pageType)
{
	freeMalloc(mem);
	freePage(page, pageType);
}

void	free(void *ptr)
{
	t_malloc	*mtmp;

	if (!ptr)
	   return ;
	if ((mtmp = findPointer(ptr, &line.tiny)))
		return (freeMemory(mtmp, &line.tiny, 't'));
	if ((mtmp = findPointer(ptr, &line.small)))
		return (freeMemory(mtmp, &line.small, 's'));
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
