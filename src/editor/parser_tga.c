/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tga.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 10:34:39 by ydonse            #+#    #+#             */
/*   Updated: 2020/02/07 10:34:58 by ydonse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_image		*initialize_image(void)
{
	t_image	*image;

	image = NULL;
	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (0);
	image->w = 0;
	image->h = 0;
	image->tex = NULL;
	image->bits_color = 0;
	image->bits_alpha = 0;
	return (image);
}

void		print_bit(char c)
{
	int		i;
	char	d;

	i = 7;
	while (i >= 0)
	{
		d = (c >> i--) & 1;
		ft_putchar(d + 48);
	}
	write(1, "\n", 1);
}

int			get_info_header(t_image *image, unsigned char *str)
{
	image->bits_alpha = str[17] << 4 >> 4;
	image->bits_color = str[16];
	image->w = str[13];
	image->w = (image->w << 8) + str[12];
	image->h = str[15];
	image->h = (image->h << 8) + str[14];
	if (image->h <= 1 || image->w <= 1 || image->h >= 4096 || image->w >= 4096)
	{
		ft_memdel((void **)&image);
		return (0);
	}
	if (!(image->tex = (Uint32 *)malloc(sizeof(Uint32)
	* (image->w * image->h + 1))))
	{
		ft_memdel((void **)&image);
		return (0);
	}
	ft_bzero(image->tex, sizeof(image->tex));
	return (1);
}

t_image		*load_tga(char *path, int i, int idx, int ret)
{
	unsigned char	str[PARSE_BUFF_SIZE];
	t_image			*image;
	int				fd;

	ft_bzero(str, PARSE_BUFF_SIZE);
	image = initialize_image();
	fd = open(path, O_RDONLY);
	if (fd == -1 || (ret = read(fd, str, 18)) < 18)
	{
		ft_memdel((void **)&image);
		return (0);
	}
	if (get_info_header(image, str) == 0)
		return (0);
	while ((ret = read(fd, str, PARSE_BUFF_SIZE)) != 0)
	{
		i = 0;
		while (i < ret && idx < image->h * image->w)
		{
			image->tex[idx++] = ((str[i]) << 8) + (str[i + 1] << 16)
			+ (str[i + 2] << 24);
			i += 4;
		}
	}
	return (image);
}
