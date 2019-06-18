/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 13:48:12 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 11:54:39 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_integer_table(int *tab, int size)
{
	int	temp;
	int i;

	i = 0;
	if (tab)
	{
		while (i < size)
		{
			if (tab[i] > tab[i + 1] && i + 1 < size)
			{
				temp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = temp;
				i = 0;
			}
			else
				i++;
		}
	}
}
