/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 16:28:45 by clanier           #+#    #+#             */
/*   Updated: 2017/12/01 21:19:33 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	free_malloc(t_malloc *mem)
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

void	free_page(void **page, char pageType)
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
	line.limit += ptmp->size + sizeof(t_page);
	munmap((void*)ptmp, ptmp->size + sizeof(t_page));
	ptmp = NULL;
}

void		*find_pointer(void *ptr, void **page)
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

void	free_memory(t_malloc *mem, void **page, char pageType)
{
	free_malloc(mem);
	free_page(page, pageType);
}

void	free(void *ptr)
{
	t_malloc	*mtmp;

	if (!ptr)
	   return ;
	if ((mtmp = find_pointer(ptr, &line.tiny)))
		return (free_memory(mtmp, &line.tiny, 't'));
	if ((mtmp = find_pointer(ptr, &line.small)))
		return (free_memory(mtmp, &line.small, 's'));
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
		line.limit += mtmp->size + sizeof(t_malloc);
		munmap(mtmp, mtmp->size + sizeof(t_malloc));
	}
}
