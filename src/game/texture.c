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

void	ft_limit_portal_texture(t_multithread *mt, int end, int *limit_ceiling, int *limit_floor)
{
	int	diff_haute; // en metre ig
	int	diff_total; // en metre ig
	int	diff_total_pxl; // en pixel
	int	diff_basse; // en metre ig

	diff_haute = mt->wall->ceiling_height - mt->wall->ceiling_height_dest;
	diff_basse = mt->wall->floor_height_dest - mt->wall->floor_height;
	diff_total = mt->wall->ceiling_height - mt->wall->floor_height;
	diff_total_pxl = mt->wall_height_tmp;
	*limit_ceiling = (end - mt->wall_height_tmp) + ((diff_haute * 100 / diff_total) * diff_total_pxl) / 100;
	*limit_floor = end - ((diff_basse * 100 / diff_total) * diff_total_pxl) / 100;
}

void 	draw_texture(t_multithread *mt, t_pos coord, int end)
{
	// static pthread_mutex_t	mutex_stock = PTHREAD_MUTEX_INITIALIZER;
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
	if (mt->wall->wall_or_portal == 'p')
		ft_limit_portal_texture(mt, end, &limit_ceiling, &limit_floor);
	begin_wall = coord.y;
	y = 1;
	if (begin_wall < 0)
		y += abs(begin_wall);

	x = mt->wall->total_width_wall - mt->wall->screen_width_wall + mt->avcm_x;
	if ((mt->wall->left.x == mt->wall->r_left.x) && (mt->wall->left.y
		== mt->wall->r_left.y) && ((mt->wall->right.x != mt->wall->r_right.x)
		|| (mt->wall->right.y != mt->wall->r_right.y)))
		x = mt->avcm_x;
	else if (((mt->wall->left.x != mt->wall->r_left.x) || (mt->wall->left.y
		!= mt->wall->r_left.y)) && ((mt->wall->right.x != mt->wall->r_right.x)
		|| (mt->wall->right.y != mt->wall->r_right.y)))
		x = mt->wall->left_void_side + mt->avcm_x;
	nb_tex_x = (ft_dist_t_dpos(mt->wall->r_left, mt->wall->r_right) / METRE) / 2;
	nb_tex_y = abs(mt->wall->floor_height - mt->wall->ceiling_height);
	tex_size_x = mt->wall->total_width_wall / nb_tex_x;
	tex_size_y = (end - coord.y) / nb_tex_y;
	perx = (fmod((double)x, tex_size_x)) * 100 / tex_size_x;
	if (coord.y < 0)
		coord.y = 0;
	if (limit_floor > HEIGHT)
		limit_floor = HEIGHT;
	if ((mt->wall->wall_or_portal == 'p') && (coord.y > limit_ceiling))
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
		if (mt->wall->wall_or_portal == 'p')
		{
			if (coord.y == limit_ceiling)
			{
				coord.y = limit_floor;
				y = 0;
			}
		}
		pery = (fmod((double)y, tex_size_y)) * 100 / tex_size_y;
		px = (int)((pery * (double)mt->wall->image->h) / 100) * mt->wall->image->w
			+ (int)((perx * (double)mt->wall->image->w) / 100);
		// pthread_mutex_lock(&mutex_stock);
		if (px >= 0 && px < mt->wall->image->w * mt->wall->image->h && mt->wall->image->tex[px] != 65280)
			set_pixel(mt->s->sdl->game, mt->wall->image->tex[px], coord);
		// pthread_mutex_unlock(&mutex_stock);
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
