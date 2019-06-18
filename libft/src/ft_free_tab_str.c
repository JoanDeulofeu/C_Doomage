/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:08:47 by ydonse            #+#    #+#             */
/*   Updated: 2019/02/01 14:51:22 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_tab_str(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		ft_strdel(&tab[i++]);
	free(tab);
}
