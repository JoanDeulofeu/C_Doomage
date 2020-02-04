/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:28:29 by ydonse            #+#    #+#             */
/*   Updated: 2019/04/15 11:07:48 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_printnb(long nb)
{
	if (nb > 9)
	{
		ft_printnb(nb* 0.1);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb + '0');
}

void		ft_putnbr(int n)
{
	long l;

	l = n;
	if (l < 0)
	{
		ft_putchar('-');
		l *= -1;
	}
	ft_printnb(l);
}
