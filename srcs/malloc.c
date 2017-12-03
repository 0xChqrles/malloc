/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 15:36:00 by clanier           #+#    #+#             */
/*   Updated: 2017/12/03 20:21:23 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		create_page(size_t alloc_max, void **page, t_page *prev)
{
	size_t	size;
	size_t	page_size;

	page_size = getpagesize();
	size = 100 * (alloc_max + sizeof(t_malloc)) + sizeof(t_page);
	if (size % page_size)
		size += page_size - size % page_size;
	if (size > g_line.limit
	|| (*page = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0)) == MAP_FAILED)
		return (-1);
	g_line.limit -= size;
	init_page(size, page, prev);
	return (0);
}

void	*set_malloc(size_t size, t_malloc **mem)
{
	t_malloc	*new;

	new = (void*)((size_t)*mem + sizeof(t_malloc) + size);
	new->size = (*mem)->size - size - sizeof(t_malloc) - 1;
	new->is_free = true;
	new->next = (*mem)->next;
	new->prev = *mem;
	(*mem)->next = new;
	(*mem)->is_free = false;
	(*mem)->size = size;
	return ((void*)((size_t)*mem + sizeof(t_malloc)));
}

void	*get_free_memory(size_t size, void **page, size_t size_max)
{
	t_malloc	*mtmp;
	t_page		*ptmp;

	ptmp = (t_page*)(*page);
	while (ptmp)
	{
		mtmp = ptmp->first;
		while (mtmp)
		{
			if (mtmp->is_free && mtmp->size > size + sizeof(t_malloc))
				return (set_malloc(size, &mtmp));
			else if (mtmp->is_free && mtmp->size >= size)
			{
				mtmp->is_free = false;
				return ((void*)((size_t)mtmp + sizeof(t_malloc)));
			}
			mtmp = mtmp->next;
		}
		ptmp = (t_page*)ptmp->next;
	}
	if (create_page(size_max, page, *page) < 0)
		return (NULL);
	ptmp = (t_page*)(*page);
	mtmp = ptmp->first;
	return (set_malloc(size, &mtmp));
}

void	*large_malloc(size_t size)
{
	void		*ptr;
	t_malloc	*tmp;
	t_malloc	*new;

	size += sizeof(t_malloc);
	if (g_line.limit < size
	|| (ptr = mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0)) == MAP_FAILED)
		return (NULL);
	g_line.limit -= size;
	new = (t_malloc*)ptr;
	new->next = NULL;
	new->prev = NULL;
	new->is_free = false;
	new->size = size - sizeof(t_malloc);
	if (!g_line.large)
		g_line.large = new;
	else
	{
		tmp = g_line.large;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (new + sizeof(t_malloc));
}

void	*ft_malloc(size_t size)
{
	if ((!g_line.tiny && init() < 0) || size <= 0)
		return (NULL);
	if (size < TINY)
		return (get_free_memory(size, &g_line.tiny, TINY));
	if (size < SMALL)
		return (get_free_memory(size, &g_line.small, SMALL));
	return (large_malloc(size));
}
