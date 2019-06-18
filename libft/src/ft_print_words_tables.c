/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_words_tables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 17:32:55 by ydonse            #+#    #+#             */
/*   Updated: 2018/11/21 12:05:23 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_words_tables(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (tab)
	{
		while (tab[i])
		{
			while (tab[i][j])
			{
				ft_putchar(tab[i][j]);
				j++;
			}
			ft_putchar('\n');
			j = 0;
			i++;
		}
	}
}
