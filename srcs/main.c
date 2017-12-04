/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:03:38 by clanier           #+#    #+#             */
/*   Updated: 2017/12/04 17:45:39 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	if (g_line.env & ENV_VERBOSE)
	{
		ft_putstr("\033[36m[  MALLOC  ] \033[1m");
		ft_putnbr_base(size, 10);
		ft_putstr("\033[0m\033[36m bytes\033[0m\n");
	}
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	if (g_line.env & ENV_VERBOSE)
	{
		ft_putstr("\033[32m[   FREE   ] \033[1m");
		ft_putnbr_base(g_line.old_size, 10);
		ft_putstr("\033[0m\033[32m bytes\033[0m\n");
	}
	pthread_mutex_unlock(&g_mutex);
}

void			*realloc(void *ptr, size_t size)
{
	void	*new;

	pthread_mutex_lock(&g_mutex);
	new = ft_realloc(ptr, size);
	if (g_line.env & ENV_VERBOSE)
	{
		ft_putstr("\033[35m[ RE-ALLOC ] \033[1m");
		ft_putnbr_base(g_line.old_size, 10);
		ft_putstr("\033[0m\033[35m -> \033[1m");
		ft_putnbr_base(size, 10);
		ft_putstr("\033[0m\033[35m bytes\033[0m\n");
	}
	pthread_mutex_unlock(&g_mutex);
	return (new);
}

void			show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	ft_show_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
}

void			*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_calloc(count, size);
	if (g_line.env & ENV_VERBOSE)
	{
		ft_putstr("\033[31m[  CALLOC  ] \033[1m");
		ft_putnbr_base(count, 10);
		ft_putstr("\033[0m\033[31m * \033[1m");
		ft_putnbr_base(size, 10);
		ft_putstr("\033[0m\033[31m = \033[1m");
		ft_putnbr_base(count * size, 10);
		ft_putstr("\033[0m\033[31m bytes\033[0m\n");
		ft_putnbr_base((size_t)ptr, 16);
		ft_putstr("\n");
	}
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
