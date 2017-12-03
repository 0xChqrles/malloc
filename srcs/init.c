/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:36:02 by clanier           #+#    #+#             */
/*   Updated: 2017/12/03 21:40:22 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*init_page(size_t size, void **page, t_page *prev)
{
	t_malloc	*mhead;
	t_page		*phead;

	mhead = (t_malloc*)(*page + sizeof(t_page));
	mhead->size = size - sizeof(t_page) - sizeof(t_malloc) - 2;
	mhead->prev = NULL;
	mhead->next = NULL;
	mhead->is_free = true;
	phead = (t_page*)(*page);
	phead->first = mhead;
	phead->prev = prev;
	phead->next = NULL;
	phead->size = size;
	phead->end = *page + size - 1;
	if (prev)
		prev->next = *page;
	return (phead);
}

void	init_env(void)
{
	g_line.env = 0;
	if (getenv("MallocScribble"))
		g_line.env |= ENV_SCRIBBLE;
	if (getenv("MallocShowFree"))
		g_line.env |= ENV_SHOW_FREE;
}

int		init(void)
{
	struct rlimit	limit;

	init_env();
	if (!getrlimit(RLIMIT_MEMLOCK, &limit))
		g_line.limit = limit.rlim_cur;
	if ((!g_line.tiny && create_page(TINY, &g_line.tiny, NULL) < 0)
	|| (!g_line.small && create_page(SMALL, &g_line.small, NULL) < 0))
		return (-1);
	return (0);
}
