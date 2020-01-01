#include "doom.h"

void	get_wall_distance(t_walls *wall, t_visu *vs)
{
	int	dist1;
	int dist2;

	dist1 = ft_dist_t_dpos(wall->left, vs->player);
	dist2 = ft_dist_t_dpos(wall->right, vs->player);
	if (dist1 <= dist2)
	{
		wall->l_dist = dist1;
		wall->b_dist = dist2;
	}
	else
	{
		wall->l_dist = dist2;
		wall->b_dist = dist1;
	}
}

void	ft_draw_column(t_main *s, t_walls *wall, t_pos coord, int end, Uint32 color)
{
	coord.y = ft_draw_ceiling(s, wall, coord);

	if (((wall->wall_or_portal == 'w') || (wall->wall_or_portal == 'p'
		&& (wall->floor_height_dest > wall->floor_height
		|| wall->ceiling_height_dest < wall->ceiling_height))) && coord.y < HEIGHT)
	{
		if (wall->image)
			draw_texture(s, wall, coord, end);
		else
		{
			if (coord.y < 0)
				coord.y = -1;
			while (coord.y++ < end)
				set_pixel(s->sdl->game, color, coord);
		}
	}
	coord.y = end - 1;
	if (coord.y < HEIGHT)
		ft_draw_floor(s, wall, coord);
}

int		ft_get_diff_height_pxl(double eyesight, int ceiling_height, int floor_height, int height_wall)
{
	int		ig_height_wall; // hauteur du mur in game (en metre)
	double	pct_eyesight; //pourcentage vision player

	ig_height_wall = ceiling_height - floor_height;
	pct_eyesight = (eyesight * 100 / ig_height_wall);
	// printf("pct = %.2f      ", pct_eyesight);
	return ((pct_eyesight * height_wall) / 100);
}

int		ft_draw_wall(t_main *s, t_walls *wall, double l_height_wall, double r_height_wall, int width_wall)
{
	double	diff_wall;
	int		i;
	double	height_wall;
	t_pos	coord;
	int		bottom;
	double	pct_avcm; //pourcentage avancement
	double	diff_height_pxl;
	double	eyesight;

	i = 0;
	diff_wall = fabs(l_height_wall - r_height_wall);
	height_wall = l_height_wall;
	coord.x = wall->x;
	get_total_w_wall(wall);
	s->player.eyesight = s->player.foot_height - wall->floor_height + s->player.size;
	eyesight = s->player.eyesight;
	// printf("---\nwall size = %d       player size %d      player eyesight %d\n", wall->ceiling_height - wall->floor_height, s->player.size, s->player.eyesight);
	while (i++ <= width_wall)
	{
		// printf("---\nwall size = %d - player size %d - player eyesight %d - floor height %d\n", wall->ceiling_height - wall->floor_height, s->player.size, s->player.eyesight, wall->floor_height);
		wall->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(eyesight, wall->ceiling_height, wall->floor_height, height_wall);
		// printf("height = %.2f      diff = %.2f\n", height_wall, diff_height_pxl);
		coord.y = (HEIGHT / 2) - (height_wall) + s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT / 2) + s->player.y_eye + diff_height_pxl;
		if (coord.x > 0 && coord.x < WIDTH)
		{
			if (i == 1 || i == width_wall)
				ft_draw_column(s, wall, coord, bottom, 0x000000FF);
			else
				ft_draw_column(s, wall, coord, bottom, 0xb0842fff);
		}

		coord.x++;
		pct_avcm = (100 * (double)i) / (double)width_wall;

		if (l_height_wall < r_height_wall)
			height_wall = l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (l_height_wall > r_height_wall)
			height_wall = l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = l_height_wall;
	}
	// printf("-----------------------------------------------\n\n\n\n");
	return (coord.x);
}
