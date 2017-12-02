/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:37:00 by clanier           #+#    #+#             */
/*   Updated: 2017/12/01 21:31:58 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

bool	is_empty(t_page *page)
{
	t_malloc	*mtmp;

	while (page)
	{
		mtmp = page->first;
		while (mtmp)
		{
			if (!mtmp->isFree)
				return (false);
			mtmp = mtmp->next;
		}
		page = page->next;
	}
	return (true);
}

size_t	show_page(t_page *page, char *pageName)
{
	t_malloc	*mtmp;
	size_t		from;
	size_t		total;

	if (is_empty(page))
		return (0);
	ft_printf("%s : 0x%lX\n", pageName, (unsigned long)page->first);
	total = 0;
	while (page)
	{
		mtmp = page->first;
		while (mtmp)
		{
			if (!mtmp->isFree)
			{
				total += mtmp->size;
				from = (unsigned long)(mtmp + sizeof(t_malloc));
				printf("0x%lX - 0x%lX : %lu octets\n",
				from, from + mtmp->size, mtmp->size);
			}
			mtmp = mtmp->next;
		}
		page = page->next;
	}
	return (total);
}

void	show_alloc_mem()
{
	t_malloc	*large;
	size_t		total;
	size_t		from;

	total = show_page(line.tiny, "TINY");
	total += show_page(line.small, "SMALL");
	if (!line.large)
	{
		printf("Total : %lu octets\n", total);
		return ;
	}
	ft_printf("LARGE : 0x%lX\n", (unsigned long)line.large);
	large = line.large;
	while (large)
	{
		total += large->size;
		from = (unsigned long)(large + sizeof(t_malloc));
		printf("0x%lX - 0x%lX : %lu octets\n",
		from, from + large->size, large->size);
		large = large->next;
	}
	printf("Total : %lu octets\n", total);
}
