/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:03:38 by clanier           #+#    #+#             */
/*   Updated: 2017/12/02 17:53:24 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void			*malloc(size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void			free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void			*realloc(void *ptr, size_t size)
{
	void	*new;

	pthread_mutex_lock(&g_mutex);
	new = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (new);
}

void			show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	ft_show_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
}

void			*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_calloc(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
