#include "doom.h"

double  to_rad(double angle)
{
    return (angle * M_PI / 180.0);
}

double  to_degres(double rad)
{
    return (rad * 180.0 / M_PI);
}

int		arround(int space, int nb)
{
	int    res;
	int    res2;

	res = nb / space;
	res2 = res + 1;
	return (nb - (space * res) > space * res2
	- nb ? space * res2 : space * res);
}

double	percent(double value, double total)
{
	return (value / total);
}

t_pos 	get_px_r_pos(t_main *s, t_dpos ref)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;

	correc = 0;
	edi = s->editor;
	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (ref.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (ref.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	return (pos);
}

t_pos 	get_px_pos(t_main *s, t_pos ref)
{
	t_pos		pos;
	t_editor 	*edi;
	int 		correc;

	correc = 0;
	edi = s->editor;
	if (edi->decal_x <= 0)
		correc = edi->decal_x % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.x = (ref.x - edi->ref.x + correc) * edi->space + (edi->decal_x % edi->space);
	if (edi->decal_y <= 0)
		correc = edi->decal_y % edi->space != 0 ? 1 : 0;
	else
		correc = 0;
	pos.y = (ref.y - edi->ref.y + correc) * edi->space + (edi->decal_y % edi->space);
	return (pos);
}

t_dpos	get_abs_r_pos(t_main *s, t_pos ori)
{
	t_dpos	res;
  t_editor *edi;

  edi = s->editor;
	res.x = 0;
	res.y = 0;
  res.x = ori.x - edi->decal_x;
  res.x = (res.x / edi->space);
  res.y = ori.y - edi->decal_y;
	res.y = (res.y / edi->space);
	return (res);
}


t_pos	get_abs_pos(t_main *s, t_pos ori)
{
	t_pos	res;
	int		correc_x;
	int		correc_y;

	res.x = 0;
	res.y = 0;
	correc_x = 0;
	correc_y = 0;
	if (s->editor->decal_x % s->editor->space != 0 && s->editor->decal_x < 0)
		correc_x = -1;
	if (s->editor->decal_y % s->editor->space != 0 && s->editor->decal_y < 0)
		correc_y = -1;
	res.x = s->editor->ref.x + (ori.x / s->editor->space) + correc_x;
	res.y = s->editor->ref.y + (ori.y / s->editor->space) + correc_y;
	return (res);
}

void	ft_reset_color_screen(Uint32 *str, int size)
{
	int i;

	i = -1;
	while (++i < size)
		str[i] = 0x13131dFF; // #13131d
}

Uint32	get_pixel_color(t_texture *text, int x, int y)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
		return (text->content[x + y * WIDTH]);
	else
		return (2);
}

t_dpos	ft_pos_to_dpos(t_pos pos)
{
	t_dpos	dpos;

	dpos.x = (float)pos.x;
	dpos.y = (float)pos.y;
	return (dpos);
}

t_pos	ft_dpos_to_pos(t_dpos dpos)
{
	t_pos	pos;

	pos.x = (int)dpos.x;
	pos.y = (int)dpos.y;
	return (pos);
}

double      calc_sprite_dist(t_main *s, t_pos pos)
{
  t_dpos    distance;
  double    dist;

  distance.x =  pos.x - s->player.pos.x;
  distance.y =  pos.y - s->player.pos.y;
  dist = (distance.x * distance.x) + (distance.y * distance.y);
  dist = sqrt(dist);
  return (dist);
}

double      calc_sprite_r_dist(t_main *s, t_dpos pos)
{
  t_dpos    distance;
  double    dist;

  distance.x =  pos.x - s->player.r_pos.x;
  distance.y =  pos.y - s->player.r_pos.y;
  dist = (distance.x * distance.x) + (distance.y * distance.y);
  dist = sqrt(dist);
  return (dist);
}
