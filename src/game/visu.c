#include "doom.h"

int		ft_find_wall(t_main *s, double angle, Uint32 color)
{
	t_sector	*sct;
	t_vertex	*vtx;
	t_int		*s_vtx;
	t_dpos		wall1;
	t_dpos		wall2;
	t_dpos		i_line; //ligne imaginaire
	int			id = 0;
	int			id_wall = 1;

	(void)color;

	sct = s->sector;
	while (s->player.sector_id != sct->id)
		sct = sct->next;
	s_vtx = sct->vertex;
	while (s_vtx->next)
	{
		id = s_vtx->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall1.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall1.y = vtx->y * s->editor->space + s->editor->decal_y;

		id = s_vtx->next->value;
		vtx = s->vertex;
		while (vtx->id != id && vtx->next)
			vtx = vtx->next;
		wall2.x = vtx->x * s->editor->space + s->editor->decal_x;
		wall2.y = vtx->y * s->editor->space + s->editor->decal_y;
		i_line.x = s->player.pos.x + cos(to_rad(angle)) * 1000;
		i_line.y = s->player.pos.y - sin(to_rad(angle)) * 1000;

		s->line.x1 = s->player.pos.x;
		s->line.y1 = s->player.pos.y;
		s->line.x2 = i_line.x;
		s->line.y2 = i_line.y;
		// get_line(s, color);

		if (ft_find_intersection(s, wall1, wall2, s->player.pos, i_line) > 0)
		{
			return (id_wall);
		}

		id_wall++;
		s_vtx = s_vtx->next;
	}
	return (id_wall);
}

void	vline(t_main *s, int x, int y1, int y2, Uint32 top, Uint32 middle, Uint32 bottom)
{
	t_pos coord;
	int y;

	y = 0;
	y1 = clamp(y1, 0, HEIGHT - 1);
	y2 = clamp(y2, 0, HEIGHT - 1);
	coord.x = x;
	coord.y = y1;
	if (y2 == y1)
	{
		set_pixel(s->sdl->game, middle, coord);
	}
	else if (y2 > y1)
	{
		set_pixel(s->sdl->game, top, coord);
		y = y1 + 1;
		while (y < y2)
		{
			coord.y = y;
			set_pixel(s->sdl->game, middle, coord);
			y++;
		}
		set_pixel(s->sdl->game, bottom, coord);
	}
}

double		vxs(double x1, double y1, double x2, double y2)
{
	return ((x1 * y2) - (x2 * y1));
}

t_dpos	intersect(t_dpos pos1, t_dpos pos2, t_dpos pos3, t_dpos pos4)
{
	t_dpos new_pos;
	int calcul2;

	calcul2 = vxs(pos1.x - pos2.x, pos1.y - pos2.y,
		pos3.x - pos4.x, pos3.y - pos4.y);

	new_pos.x = vxs(vxs(pos1.x, pos1.y, pos2.x, pos2.y),
	pos1.x - pos2.x, vxs(pos3.x, pos3.y, pos4.x, pos4.y), pos3.x - pos4.x)
	/ calcul2;
	new_pos.y =  vxs(vxs(pos1.x, pos1.y, pos2.x, pos2.y),
	pos1.y - pos2.y, vxs(pos3.x, pos3.y, pos4.x, pos4.y), pos3.y - pos4.y)
	/ calcul2;
	return (new_pos);
}

int		check_vtx_nb(t_sector *tmp_sct)
{
	int		res;
	t_int	*tmp_vertex;


	tmp_vertex = tmp_sct->vertex;
	res = 0;
	while (tmp_vertex)
	{
		tmp_vertex = tmp_vertex->next;
		res++;
	}
	return (res);
}

t_int	*get_wall_vertex(t_sector *tmp_sct, int wall_id)
{
	t_int		*temp;
	int			i;

	temp = tmp_sct->vertex;
	i = 1;
	while (i++ < wall_id)
		temp = temp->next;
	return (temp);
}

int 	get_vtx_wall_value(t_sector *tmp_sct, t_int *vtx)
{
	t_int	*wall;

	wall = tmp_sct->wall;
	while (vtx->id != wall->id)
		wall = wall->next;
	return (wall->value);
}

void	ft_visu_wall(t_main *s)
{
	int			nb_vtx;
	int			i = 0;
	t_sector	*tmp_sct;
	// t_int		*vertex1_wall1;
	// t_int		*vertex2_wall1;
	t_pos		beg_wall1;
	t_pos		end_wall1;
	// t_pos		beg_wall2;
	// t_pos		end_wall2;
	t_dpos		player;
	float		vx1;
	float		vx2;
	float		vy1;
	float		vy2;
	float		pcos;
	float		psin;
	float		tx1;
	// float		ty1;
	float		tx2;
	// float		ty2;
	float		tz1;
	float		tz2;
	int ytop[WIDTH] = {0};
	int ybottom[WIDTH] = {0};
	t_int *vtx;

	// printf("angle du joueur = %f\n", s->player.angle);
	// if (wall1_id > wall2_id)
	tmp_sct = get_sector_by_id(s, s->player.sector_id);
	nb_vtx = check_vtx_nb(tmp_sct);
	//verifier que les vertex sont bien les bons avec la structure de mort de joan
	vtx = tmp_sct->vertex;
	// printf("nb walls = %d\n", nb_walls);
	while (i < WIDTH)
		ybottom[i++] = HEIGHT - 1;
	i = 0;
	// vertex1_wall1 = (get_t_int_by_id(tmp_sct->vertex, wall1_id))->ptr->x;

	if (s->player.p_ori.x < 0)
		player.x = (s->player.ori.x - s->editor->ref.x) - (((double)ft_abs(s->player.p_ori.x) / (double)s->editor->space));
	else if(s->player.p_ori.x > 0)
		player.x = (s->player.ori.x - s->editor->ref.x) + (((double)ft_abs(s->player.p_ori.x) / (double)s->editor->space));
	else
		player.x = (s->player.ori.x - s->editor->ref.x);
	if (s->player.p_ori.y < 0)
		player.y = (s->player.ori.y - s->editor->ref.y) - (((double)ft_abs(s->player.p_ori.y) / (double)s->editor->space));
	else if(s->player.p_ori.y > 0)
		player.y = (s->player.ori.y - s->editor->ref.y) + (((double)ft_abs(s->player.p_ori.y) / (double)s->editor->space));
	else
		player.y = (s->player.ori.y - s->editor->ref.y);
	//printf("player.x = %f   ", player.x);
	//printf("player.y = %f\n\n", player.y);

	while (i < nb_vtx)
	{
		beg_wall1.x = (vtx->ptr->x - s->editor->ref.x);
		beg_wall1.y = (vtx->ptr->y - s->editor->ref.y);
		if (vtx->next)
		{
			end_wall1.x = (vtx->next->ptr->x - s->editor->ref.x);
			end_wall1.y = (vtx->next->ptr->y - s->editor->ref.y);
		}
		else
		{
			end_wall1.x = (tmp_sct->vertex->ptr->x - s->editor->ref.x);
			end_wall1.y = (tmp_sct->vertex->ptr->y - s->editor->ref.y);
		}
		vx1 = beg_wall1.x - player.x;
		vy1 = beg_wall1.y - player.y;
		vx2 = end_wall1.x - player.x;
		vy2 = end_wall1.y - player.y;
		pcos = cos(to_rad(s->player.angle));
		psin = sin(to_rad(s->player.angle));
		tx1 = vx1 * psin - vy1 * pcos;
		tz1 = vx1 * pcos + vy1 * psin;
		tx2 = vx2 * psin - vy2 * pcos;
		tz2 = vx2 * pcos + vy2 * psin;
		if (tz1 <= 0 && tz2 <= 0)
		{
			i++;
			vtx = vtx->next;
			continue;
		}
		if (tz1 <= 0 || tz2 <= 0)
		{
			float nearz = 1e-4f;
			float farz = 5;
			float nearside = 1e-5f;
			float farside = 20.f;
			t_dpos inter1;
			t_dpos inter2;
			t_dpos inter3;
			t_dpos inter4;
			t_dpos i1;
			t_dpos i2;
			inter1.x = tx1;
			inter1.y = tz1;
			inter2.x = tx2;
			inter2.y = tz2;
			inter3.x = -nearside;
			inter3.y = nearz;
			inter4.x = -farside;
			inter4.y = farz;
			i1 = intersect(inter1, inter2, inter3, inter4);
			inter3.x = nearside;
			inter4.x = farside;
			i2 = intersect(inter1, inter2, inter3, inter4);
			if (tz1 < nearz)
			{
				if (i1.y > 0)
				{
					tx1 = i1.x;
					tz1 = i1.y;
				}
				else
				{
					tx1 = i2.x;
					tz1 = i2.y;
				}
			}
			if (tz2 < nearz)
			{
				if (i1.y > 0)
				{
					tx2 = i1.x;
					tz2 = i1.y;
				}
				else
				{
					tx2 = i2.x;
					tz2 = i2.y;
				}
			}
		}
		//do perspective transformation
			float xscale1 = HFOV / tz1;
			float yscale1 = VFOV / tz1;
			float xscale2 = HFOV / tz2;
			float yscale2 = VFOV / tz2;
			int x1 = WIDTH / 2 - (int)(tx1 * xscale1);
			int x2 = WIDTH / 2 - (int)(tx2 * xscale2);
			if (x1 >= x2 || x2 < 0 || x1 > WIDTH - 1)
			{
				i++;
				vtx = vtx->next;
				continue;
			}
			float yceil = tmp_sct->ceiling - (s->player.sector->floor + s->player.eyesight);
			float yfloor = tmp_sct->floor - (s->player.sector->floor + s->player.eyesight);
			//check the edge type. neighbor = -1 means wall
			int neighbor = get_vtx_wall_value(tmp_sct, vtx);
			float nyceil = 0;
			float nyfloor = 0;
			if (neighbor >= 0)
			{
				t_sector *next;
				next = get_sector_by_id(s, neighbor);
				nyceil = next->ceiling - (s->player.sector->floor + s->player.eyesight);
				nyfloor = next->floor - (s->player.sector->floor +  s->player.eyesight);
			}
			//On projette les hauteurs du plafond et sol en coordonees de l'ecran
			int y1a = HEIGHT / 2 - (int)(yceil * yscale1);
			int y1b = HEIGHT / 2 - (int)(yfloor * yscale1);
			int y2a = HEIGHT / 2 - (int)(yceil * yscale2);
			int y2b = HEIGHT / 2 - (int)(yfloor * yscale2);

			int ny1a = HEIGHT / 2 - (int)(nyceil * yscale1);
			int ny1b = HEIGHT / 2 - (int)(nyfloor * yscale1);
			int ny2a = HEIGHT / 2 - (int)(nyceil * yscale2);
			int ny2b = HEIGHT / 2 - (int)(nyfloor * yscale2);

			int beginx = x1 > 0 ? x1 : 0;
			int endx = x2 < WIDTH - 1 ? x2 : WIDTH - 1;
			int x = beginx;
			while (x < endx)
			{
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cya = clamp(ya, ytop[x], ybottom[x]);
				int cyb = clamp(yb, ytop[x], ybottom[x]);

				//render ceiling;
				vline(s, x, ytop[x], cya -1, 0x111111FF, 0x222222FF, 0x111111FF);
				//render floor
				vline(s, x, cyb + 1, ybottom[x], 0x0000FFFF, 0X0000AAFF, 0x0000FFFF);

				if (neighbor >= 0)
				{
					//Same for their floor and ceiling
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnya = clamp(nya, ytop[x], ybottom[x]);
					int cnyb = clamp(nyb, ytop[x], ybottom[x]);
					//if our ceiling is higher than their ceiling, render upper wall
					vline(s, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : 0xAAAAAAFF, 0);
					ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1); // On rapetisse la fenetre en dessous des plafonds

					// Si le sol est plus petit que le sol suivant, on l'affiche
					vline(s, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : 0x7C00D9FF, 0);
					ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);
					vline(s, x, ytop[x], ybottom[x], 0x00AA00FF, 0x00AA00FF, 0x00AA00FF);
				}
				else
				{
					vline(s, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : COLOR_WALL, 0);
				}
				x++;
			}
			vtx = vtx->next;


		i++;
	}

}


void	ft_visu(t_main *s)
{
	int		mur1;
	int		mur2;
	int		angle;
	Uint32	color = 0x25f902ff; //#25f902

	s->player.sector_id= ft_is_in_sector(s, ft_dpos_to_pos(s->player.pos));
	s->player.sector= get_sector_by_id(s, s->player.sector_id);
	angle = s->player.angle - (HFOV / 2) < 0 ? 360
	- fabs(s->player.angle - (HFOV / 2)) : (s->player.angle - (HFOV / 2));
	mur2 = ft_find_wall(s, angle, color);
	// printf("angle = %d\n", angle);
	s->intersect2.x = s->tmp_intersect.x;
	s->intersect2.y = s->tmp_intersect.y;
	// printf("id mur1 = %d, angle = %d\n", mur2, angle);
	s->line.x1 = s->player.pos.x;
	s->line.y1 = s->player.pos.y;
	s->line.x2 = s->intersect2.x;
	s->line.y2 = s->intersect2.y;
	get_line(s, color);

	color = 0xdb00ffff;
	angle = s->player.angle + (HFOV / 2);
	if (angle > 360)
		angle -= 360;
	// printf("angle = %d\n", angle);
	mur1 = ft_find_wall(s, angle, color);
	s->intersect1.x = s->tmp_intersect.x;
	s->intersect1.y = s->tmp_intersect.y;
	// printf("id mur2 = %d, angle = %d\n", mur1, angle);
	s->line.x1 = s->player.pos.x;
	s->line.y1 = s->player.pos.y;
	s->line.x2 = s->intersect1.x;
	s->line.y2 = s->intersect1.y;
	get_line(s, color);
	ft_visu_wall(s);

	// ft_visu_wall(s, mur1, mur2);
}
