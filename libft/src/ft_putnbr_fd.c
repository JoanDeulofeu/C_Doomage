/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 11:29:47 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/09 12:15:00 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void		ft_printnb(long nb, int fd)
{
	char c;

	if (nb > 9)
	{
		ft_printnb(nb * 0.1, fd);
		c = '0' + nb % 10;
		write(fd, &c, 1);
	}
	else
	{
		c = nb + '0';
		write(fd, &c, 1);
	}
}

void			ft_putnbr_fd(int n, int fd)
{
	long l;

	l = n;
	if (l < 0)
	{
		write(fd, "-", 1);
		l *= -1;
	}
	ft_printnb(l, fd);
}
