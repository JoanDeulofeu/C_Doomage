#include "doom.h"

void	*ft_draw_wall1(void *void_mt)
{
	double			diff_wall;
	int				i;
	double			height_wall;
	t_pos			coord;
	int				bottom;
	double			pct_avcm;
	double			diff_height_pxl;
	double			eyesight;
	t_multithread	*mt;
	int				limit_thread;

	mt = (t_multithread *)void_mt;
	diff_wall = fabs(mt->l_height_wall - mt->r_height_wall);
	height_wall = mt->l_height_wall;
	coord.x = mt->wall->x;
	eyesight = mt->s->player.foot_height - mt->wall->floor_height + mt->s->player.size;

	limit_thread = mt->width_wall / 4;
	i = 0;
	// printf("WALL(%d)  -  ft_draw_wall1 i %d        limit %d\n", mt->wall->id, i, limit_thread);

	while (i++ <= limit_thread)
	{
		mt->wall_height_tmp = height_wall;
		mt->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(eyesight, mt->wall->ceiling_height,
			mt->wall->floor_height, height_wall);
		coord.y = (HEIGHT / 2) - (height_wall) + mt->s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT / 2) + mt->s->player.y_eye + diff_height_pxl;
		if (coord.x > 0 && coord.x < WIDTH)
		{
			ft_draw_column(coord, bottom, mt);
		}
		coord.x++;
		pct_avcm = (100 * (double)i) / (double)mt->width_wall;

		if (mt->l_height_wall < mt->r_height_wall)
			height_wall = mt->l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (mt->l_height_wall > mt->r_height_wall)
			height_wall = mt->l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = mt->l_height_wall;
	}
	pthread_exit(NULL);
}

void	*ft_draw_wall2(void *void_mt)
{
	double			diff_wall;
	int				i;
	double			height_wall;
	t_pos			coord;
	int				bottom;
	double			pct_avcm;
	double			diff_height_pxl;
	double			eyesight;
	t_multithread	*mt;
	int				limit_thread;

	mt = (t_multithread *)void_mt;
	diff_wall = fabs(mt->l_height_wall - mt->r_height_wall);
	height_wall = mt->l_height_wall;
	coord.x = mt->wall->x + (mt->width_wall / 4);
	eyesight = mt->s->player.foot_height - mt->wall->floor_height + mt->s->player.size;

	limit_thread = mt->width_wall / 2;
	i = mt->width_wall / 4;
	// printf("WALL(%d)  -  ft_draw_wall1 i %d        limit %d\n", mt->wall->id, i, limit_thread);

	while (i++ <= limit_thread)
	{
		pct_avcm = (100 * (double)i) / (double)mt->width_wall;

		if (mt->l_height_wall < mt->r_height_wall)
			height_wall = mt->l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (mt->l_height_wall > mt->r_height_wall)
			height_wall = mt->l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = mt->l_height_wall;
		mt->wall_height_tmp = height_wall;
		mt->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(eyesight, mt->wall->ceiling_height,
			mt->wall->floor_height, height_wall);
		coord.y = (HEIGHT / 2) - (height_wall) + mt->s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT / 2) + mt->s->player.y_eye + diff_height_pxl;
		if (coord.x > 0 && coord.x < WIDTH)
		{
			ft_draw_column(coord, bottom, mt);
		}
		coord.x++;
	}
	pthread_exit(NULL);
}

void	*ft_draw_wall3(void *void_mt)
{
	double			diff_wall;
	int				i;
	double			height_wall;
	t_pos			coord;
	int				bottom;
	double			pct_avcm;
	double			diff_height_pxl;
	double			eyesight;
	t_multithread	*mt;
	int				limit_thread;

	mt = (t_multithread *)void_mt;
	diff_wall = fabs(mt->l_height_wall - mt->r_height_wall);
	height_wall = mt->l_height_wall;
	coord.x = mt->wall->x + (mt->width_wall / 2);
	eyesight = mt->s->player.foot_height - mt->wall->floor_height + mt->s->player.size;

	limit_thread = (mt->width_wall / 4) * 3;
	i = mt->width_wall / 2;
	// printf("WALL(%d)  -  ft_draw_wall1 i %d        limit %d\n", mt->wall->id, i, limit_thread);

	while (i++ <= limit_thread)
	{
		pct_avcm = (100 * (double)i) / (double)mt->width_wall;

		if (mt->l_height_wall < mt->r_height_wall)
			height_wall = mt->l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (mt->l_height_wall > mt->r_height_wall)
			height_wall = mt->l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = mt->l_height_wall;
		mt->wall_height_tmp = height_wall;
		mt->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(eyesight, mt->wall->ceiling_height,
			mt->wall->floor_height, height_wall);
		coord.y = (HEIGHT / 2) - (height_wall) + mt->s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT / 2) + mt->s->player.y_eye + diff_height_pxl;
		if (coord.x > 0 && coord.x < WIDTH)
		{
			ft_draw_column(coord, bottom, mt);
		}
		coord.x++;

	}
	pthread_exit(NULL);
}

void	*ft_draw_wall4(void *void_mt)
{
	double			diff_wall;
	int				i;
	double			height_wall;
	t_pos			coord;
	int				bottom;
	double			pct_avcm;
	double			diff_height_pxl;
	double			eyesight;
	t_multithread	*mt;
	int				limit_thread;

	mt = (t_multithread *)void_mt;
	diff_wall = fabs(mt->l_height_wall - mt->r_height_wall);
	height_wall = mt->l_height_wall;
	coord.x = mt->wall->x + (mt->width_wall / 4) * 3;
	eyesight = mt->s->player.foot_height - mt->wall->floor_height + mt->s->player.size;

	limit_thread = mt->width_wall;
	i = (mt->width_wall / 4) * 3;
	// printf("WALL(%d)  -  ft_draw_wall1 i %d        limit %d\n", mt->wall->id, i, limit_thread);

	while (i++ <= limit_thread)
	{
		pct_avcm = (100 * (double)i) / (double)mt->width_wall;

		if (mt->l_height_wall < mt->r_height_wall)
			height_wall = mt->l_height_wall + (diff_wall * pct_avcm) / 100;
		else if (mt->l_height_wall > mt->r_height_wall)
			height_wall = mt->l_height_wall - (diff_wall * pct_avcm) / 100;
		else
			height_wall = mt->l_height_wall;
		mt->wall_height_tmp = height_wall;
		mt->avcm_x = i;
		diff_height_pxl = ft_get_diff_height_pxl(eyesight, mt->wall->ceiling_height,
			mt->wall->floor_height, height_wall);
		coord.y = (HEIGHT / 2) - (height_wall) + mt->s->player.y_eye + diff_height_pxl;
		bottom = (HEIGHT / 2) + mt->s->player.y_eye + diff_height_pxl;
		if (coord.x > 0 && coord.x < WIDTH)
		{
			ft_draw_column(coord, bottom, mt);
		}
		coord.x++;
	}
	pthread_exit(NULL);
}

void	ft_fill_mt(t_multithread *mt, t_walls *wall, double l_height_wall, double r_height_wall, int width_wall)
{
	mt->wall = wall;
	mt->l_height_wall = l_height_wall;
	mt->r_height_wall = r_height_wall;
	mt->width_wall = width_wall;
}

void	ft_fucking_threading(t_main *s, t_walls *wall, double l_height_wall, double r_height_wall, int width_wall)
{
	int	i;
	t_multithread mt[4];
	pthread_t thread[4];
	
	i = -1;
	get_total_w_wall(wall);

	mt[++i].s = s;
	ft_fill_mt(&mt[i], wall, l_height_wall, r_height_wall, width_wall);
	if (pthread_create(&thread[i], NULL, ft_draw_wall1, (void *)(&mt[i])) == -1)
		perror("thread creation");
	mt[++i].s = s;
	ft_fill_mt(&mt[i], wall, l_height_wall, r_height_wall, width_wall);
	if (pthread_create(&thread[i], NULL, ft_draw_wall2, (void *)(&mt[i])) == -1)
		perror("thread creation");
	mt[++i].s = s;
	ft_fill_mt(&mt[i], wall, l_height_wall, r_height_wall, width_wall);
	if (pthread_create(&thread[i], NULL, ft_draw_wall3, (void *)(&mt[i])) == -1)
		perror("thread creation");
	mt[++i].s = s;
	ft_fill_mt(&mt[i], wall, l_height_wall, r_height_wall, width_wall);
	if (pthread_create(&thread[i], NULL, ft_draw_wall4, (void *)(&mt[i])) == -1)
		perror("thread creation");

	i = 0;
	while (i < 4)
		if (pthread_join(thread[i++], NULL) == -1)
			perror("thread join");
}
