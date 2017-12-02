/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:16:39 by clanier           #+#    #+#             */
/*   Updated: 2017/12/02 19:24:25 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	add_to_history()
{
	
}

void	show_history()
{
	t_history	*htmp;

	htmp = line.history;
	while (htmp)
	{
		ft_putstr(htmp->isSuccess ? "\033[31,1m" : "\033[33,1m");
		ft_putstr(htmp->action);
		ft_putstr(" : ");
		ft_putnbr_base(htmp->size, 10);
		ft_putstr(" octets\033[0m\n");
		htmp = htmp->next;
	}
}
