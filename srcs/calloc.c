/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:35:22 by clanier           #+#    #+#             */
/*   Updated: 2017/12/03 19:44:10 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = s;
	i = 0;
	while (i < n)
		ptr[i++] = c;
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	n;

	n = size * count;
	if (!(ptr = ft_malloc(n)))
		return (NULL);
	ft_memset(ptr, 0, n);
	return (ptr);
}
