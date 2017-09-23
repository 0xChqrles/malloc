/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clanier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:32:31 by clanier           #+#    #+#             */
/*   Updated: 2016/11/05 17:54:00 by clanier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char c;

	c = '0';
	if (n == -2147483648)
	{
		ft_putstr("-2");
		n = 147483648;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n <= 9)
		ft_putchar(c + n);
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
