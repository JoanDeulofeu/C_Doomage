/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 19:38:04 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 17:22:12 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_recursive_power(int nb, int power)
{
	int		a;
	long	b;

	b = nb;
	if (b > 2147483647 || b < 2147483648)
		return (0);
	else
		a = b;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 1)
	{
		power--;
		a *= ft_recursive_power(a, power);
		return (a);
	}
	return (a);
}
