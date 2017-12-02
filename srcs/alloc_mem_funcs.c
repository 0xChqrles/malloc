/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:54:20 by clanier           #+#    #+#             */
/*   Updated: 2017/12/02 18:55:22 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

double	ft_pow(double n, int exp)
{
	if (exp == 0)
		return (1);
	else if (exp > 0)
		return (n * ft_pow(n, exp - 1));
	else
		return (1 / n * ft_pow(1 / n, -exp - 1));
}

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
