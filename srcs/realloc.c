/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:55:13 by clanier           #+#    #+#             */
/*   Updated: 2017/10/01 21:13:49 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	

void	*realloc(void *ptr, size_t size)
{
	t_malloc	*mtmp;

	if (mtmp = findPointer(ptr, &line.tiny))
		return (reallocMemory(mtmp));
	if (mtmp = findPointer(ptr, &line.small))
		return (reallocMemory(mtmp));
}
