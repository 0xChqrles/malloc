/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:55:13 by clanier           #+#    #+#             */
/*   Updated: 2017/12/03 20:59:07 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*move_data(t_malloc *src, void *dest, size_t size)
{
	unsigned int	i;

	i = 0;
	while (i < size && i < src->size)
	{
		((unsigned char*)(dest))[i] =
		((unsigned char*)(src + sizeof(t_malloc)))[i];
		i++;
	}
	return (dest);
}

void	*realloc_memory(void *ptr, size_t size, char page_type)
{
	t_malloc	*mtmp;
	void		*new;

	mtmp = (t_malloc*)ptr;
	if (size <= mtmp->size
	&& (page_type == 't' || (page_type == 's' && size > TINY)))
	{
		if (mtmp->size > sizeof(t_malloc)
		&& size < mtmp->size - sizeof(t_malloc))
			return (set_malloc(size, &mtmp));
		else
			return ((void*)((size_t)mtmp + sizeof(t_malloc)));
	}
	if (!(new = ft_malloc(size)))
		return (NULL);
	move_data(mtmp, new, size);
	ft_free(mtmp + sizeof(t_malloc));
	return (new);
}

void	*ft_realloc(void *ptr, size_t size)
{
	t_malloc	*mtmp;
	void		*new;

	if (!ptr)
		return (ft_malloc(size));
	if ((mtmp = find_pointer(ptr, &g_line.tiny)))
		return (realloc_memory(mtmp, size, 't'));
	if ((mtmp = find_pointer(ptr, &g_line.small)))
		return (realloc_memory(mtmp, size, 's'));
	mtmp = g_line.large;
	while (mtmp && ptr != mtmp + sizeof(t_malloc))
		mtmp = mtmp->next;
	if (mtmp && ptr == mtmp + sizeof(t_malloc))
	{
		if (mtmp->size >= size && size > SMALL)
			return (ptr);
		if (!(new = ft_malloc(size)))
			return (NULL);
		move_data(mtmp, new, size);
		ft_free(ptr);
		return (new);
	}
	return (NULL);
}
