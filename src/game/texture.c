#include "doom.h"

void	get_total_w_wall(t_walls *wall)
{
	double		dist_screen;
	double		dist_total;
	double		dist_left;
	double		perc;

	dist_screen = ft_dist_t_dpos(wall->right, wall->left);
	dist_total = ft_dist_t_dpos(wall->r_right, wall->r_left);
	dist_left = ft_dist_t_dpos(wall->left, wall->r_left);
	//---------------TOTAL------------------
	dist_total = (dist_total == 0) ? 1 : dist_total;
	perc = (dist_screen * 100) / dist_total;
	perc = (perc == 0) ? 1 : perc;
	wall->total_width_wall = (100 * wall->screen_width_wall) / perc;
	//---------------LEFT-------------------
	dist_total = (dist_total == 0) ? 1 : dist_total;
	perc = (dist_left * 100) / dist_total;
	wall->left_void_side = (perc * wall->total_width_wall) / 100;
}

void	ft_limit_portal_texture(t_walls *wall, int end, int *limit_ceiling, int *limit_floor)
{
	int	diff_haute; // en metre ig
	int	diff_total; // en metre ig
	int	diff_total_pxl; // en pixel
	int	diff_basse; // en metre ig

	diff_haute = wall->ceiling_height - wall->ceiling_height_dest;
	diff_basse = wall->floor_height_dest - wall->floor_height;
	diff_total = wall->ceiling_height - wall->floor_height;
	diff_total_pxl = wall->wall_height_tmp;

	*limit_ceiling = (end - wall->wall_height_tmp) + ((diff_haute * 100 / diff_total) * diff_total_pxl) / 100;
	*limit_floor = end - ((diff_basse * 100 / diff_total) * diff_total_pxl) / 100;
	// printf("res ceiling %d      res floor %d\n\n", ((diff_haute * 100 / diff_total) * 100) / diff_total_pxl, ((diff_basse * 100 / diff_total) * 100) / diff_total_pxl);
	// printf("begin %d | limit_ceiling %d       limit_floor %d | end %d\n\n", begin, *limit_ceiling, *limit_floor, end);
}

void 	draw_texture(t_main *s, t_walls *wall, t_pos coord, int end)
{
	int		x; //x calculé par rapport a la taille totale du mur fenetré
	int		y; //x calculé par rapport a la taille totale du mur fenetré
	double	nb_tex_x;
	double	nb_tex_y;
	double	tex_size_x;
	double	tex_size_y;
	int		perx; // pourcentage en x sur la texture.
	int		pery; // pourcentage en y sur la texture.
	int		begin_wall;
	int		px;
	int		limit_ceiling; // dans le cas dun portail.
	int		limit_floor; // dans le cas dun portail.

	limit_ceiling = 0;
	limit_floor = 0;
	if (wall->wall_or_portal == 'p')
		ft_limit_portal_texture(wall, end, &limit_ceiling, &limit_floor);
	// if (wall->id == 2 && wall->avcm_x == 50){
	// 		printf("limit_ceiling %d , limit_floor %d\n", limit_ceiling , limit_floor);
	// 		printf("height_wall %d\n", wall->wall_height_tmp);
	// 		printf("mur = %c\n", wall->wall_or_portal);
	// 		printf("floor_dest (%d) > floor (%d)\n", wall->floor_height_dest, wall->floor_height);
	// 		printf("ceiling_dest (%d) < ceiling (%d)\n", wall->ceiling_height_dest, wall->ceiling_height);
	// 		printf("end %d\n", end);
	// 	}
	begin_wall = coord.y;
	y = 1;
	if (begin_wall < 0)
		y += abs(begin_wall);

	x = wall->total_width_wall - wall->screen_width_wall + wall->avcm_x;
	if ((wall->left.x == wall->r_left.x) && (wall->left.y == wall->r_left.y) && ((wall->right.x != wall->r_right.x) || (wall->right.y != wall->r_right.y)))
		x = wall->avcm_x;
	else if (((wall->left.x != wall->r_left.x) || (wall->left.y != wall->r_left.y)) && ((wall->right.x != wall->r_right.x) || (wall->right.y != wall->r_right.y)))
		x = wall->left_void_side + wall->avcm_x;
	nb_tex_x = (ft_dist_t_dpos(wall->r_left, wall->r_right) / METRE) / 2;
	nb_tex_y = abs(wall->floor_height - wall->ceiling_height);
	tex_size_x = wall->total_width_wall / nb_tex_x;
	tex_size_y = (end - coord.y) / nb_tex_y;
	perx = (fmod((double)x, tex_size_x)) * 100 / tex_size_x;
	if (coord.y < 0)
		coord.y = 0;
	if (limit_floor > HEIGHT)
		limit_floor = HEIGHT;
	if ((wall->wall_or_portal == 'p') && (coord.y > limit_ceiling))
	{
		coord.y = limit_floor;
		if (limit_floor < 0)
			y = 0 - limit_floor;
		else
			y = 0;
	}
	if (coord.y < 0)
		coord.y = 0;
	while (coord.y < end && coord.y < HEIGHT)
	{
		if (wall->wall_or_portal == 'p')
		{
			if (coord.y == limit_ceiling)
			{
				coord.y = limit_floor;
				y = 0;
			}
		}
		pery = (fmod((double)y, tex_size_y)) * 100 / tex_size_y;
		px = (int)((pery * (double)wall->image->h) / 100) * wall->image->w
			+ (int)((perx * (double)wall->image->w) / 100);
		if (px >= 0 && px < wall->image->w * wall->image->h && wall->image->tex[px] != 65280)
			set_pixel(s->sdl->game, wall->image->tex[px], coord);
		y++;
		coord.y++;
	}
}

int		ft_draw_ceiling(t_main *s, t_walls *wall, t_pos coord)
{
	int			begin;
	double		pct;

	if ((begin = coord.y) < 0)
		return (begin);
	wall->diffx_ceiling = (wall->diffx_ceiling == 0) ? 1 : wall->diffx_ceiling;
	pct = (((double)coord.x - (double)wall->minx_ceiling) * 100) / (double)wall->diffx_ceiling;
	if ((wall->minx_ceiling == wall->left_ceiling_limit.x && wall->miny_ceiling
		== wall->right_ceiling_limit.y) || (wall->minx_ceiling
		== wall->right_ceiling_limit.x && wall->miny_ceiling
		== wall->left_ceiling_limit.y)) // si x et y mini sont pas du meme coté
		pct = 100 - pct;
	coord.y = ((pct * wall->diffy_ceiling) * 0.01) + wall->miny_ceiling;
	if (coord.y < 0)
		coord.y = 0;
	while (coord.y < begin && coord.y < HEIGHT)
	{
		set_pixel(s->sdl->game, 0x6e492eff, coord);
		coord.y++;
	}
	coord.y = begin;
	return (coord.y - 1);
}

void	ft_draw_floor(t_main *s, t_walls *wall, t_pos coord)
{
	int end;
	double pct;

	wall->diffx_floor = (wall->diffx_floor == 0) ? 1 : wall->diffx_floor;
	pct = (((double)coord.x - (double)wall->minx_floor) * 100) / ((double)wall->diffx_floor);
	if ((wall->minx_floor == wall->left_floor_limit.x
		&& wall->miny_floor == wall->right_floor_limit.y)
		|| (wall->minx_floor == wall->right_floor_limit.x
		&& wall->miny_floor == wall->left_floor_limit.y)) // si x et y mini sont pas du meme coté
		pct = 100 - pct;
	end = ((pct * wall->diffy_floor) * 0.01) + wall->miny_floor;
	if (coord.y < 0)
		coord.y = 0;
	while (coord.y < end && coord.y < HEIGHT)
	{
		set_pixel(s->sdl->game, 0xa8b08eff, coord);
		coord.y++;
	}
}
