/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:37:00 by clanier           #+#    #+#             */
/*   Updated: 2017/12/03 21:35:07 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_header(char *page_name, size_t first)
{
	ft_putstr(page_name);
	ft_putstr(" : ");
	ft_putnbr_base(first, 16);
	ft_putchar('\n');
}

void	print_total(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr_base(total, 10);
	ft_putstr(" octets\n");
}

void	print_malloc(size_t from, size_t size)
{
	ft_putnbr_base(from, 16);
	ft_putstr(" - ");
	ft_putnbr_base(from + size, 16);
	ft_putstr(" : ");
	ft_putnbr_base(size, 10);
	ft_putstr(" octets\n");
}

size_t	show_page(t_page *page, char *page_name)
{
	t_malloc	*mtmp;
	size_t		from;
	size_t		total;

	if (is_empty(page))
		return (0);
	print_header(page_name, (size_t)page->first);
	total = 0;
	while (page)
	{
		mtmp = page->first;
		while (mtmp)
		{
			if (mtmp->is_free == (g_line.env & ENV_SHOW_FREE))
			{
				total += mtmp->size;
				from = (size_t)(mtmp) + sizeof(t_malloc);
				print_malloc(from, mtmp->size);
			}
			mtmp = mtmp->next;
		}
		page = page->next;
	}
	return (total);
}

void	ft_show_alloc_mem(void)
{
	t_malloc	*large;
	size_t		total;
	size_t		from;

	total = show_page(g_line.tiny, "TINY");
	total += show_page(g_line.small, "SMALL");
	if (!g_line.large)
		return (print_total(total));
	if (g_line.env & ENV_SHOW_FREE)
		return ;
	print_header("LARGE", (size_t)g_line.large);
	large = g_line.large;
	while (large)
	{
		total += large->size;
		from = (size_t)(large) + sizeof(t_malloc);
		print_malloc(from, large->size);
		large = large->next;
	}
	print_total(total);
}
