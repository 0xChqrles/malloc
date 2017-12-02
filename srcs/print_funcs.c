/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 18:43:01 by clanier           #+#    #+#             */
/*   Updated: 2017/12/02 18:44:47 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (*s && ++i)
		s++;
	return (i);
}

int		ft_nbrlen_base(size_t x, int base)
{
	size_t	len;
	int		i;

	i = 1;
	len = base;
	while (x > len && ++i)
		len *= base;
	return (i);
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_base(size_t x, int base)
{
	int		len;
	char	n;
	double	pow;

	if (base == 16)
		ft_putstr("0x");
	len = ft_nbrlen_base(x, base) - 1;
	while (len >= 0)
	{
		pow = ft_pow(base, len);
		n = (double)x / pow;
		ft_putchar(n < 10 ? n + 48 : n + 55);
		x -= (double)n * pow;
		len--;
	}
}
