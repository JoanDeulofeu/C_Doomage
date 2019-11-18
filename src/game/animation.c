#include "doom.h"

// t_lanim		*get_anim_by_id(t_main *s, int id)
// {
// 	t_lsprite *lst;
//
// 	lst = s->lsprite;
// 	while (lst != NULL)
// 	{
// 		if (lst->id == id)
// 			return (lst->anim);
// 		lst = lst->next;
// 	}
// 	return (NULL);
// }

void		kill(t_sprite *cur)
{
	if (cur->anim.image[cur->current] != NULL)
	{
		// cur->img = cur->anim->image[cur->current];
		cur->current += 1;
	}
	else
		cur->destroy = 1;
}

void		sprite_shooting(t_main *s, t_sprite *cur)
{
	if (cur->anim.image[cur->current] != NULL)
	{
		cur->s_angle = s->player.angle + 180;
		// set_img(s, cur, 6, 0);
		cur->current = 1;
		// cur->img = cur->anim->image[cur->current];
	}
}

void		sprite_walk(t_sprite *cur)
{
	if (cur->anim.image[cur->current] == NULL)
		cur->current = 1;
	else
	{
		cur->current += 1;
		// cur->img = cur->anim->image[cur->current];
	}
}

void		play_anim(t_main *s)
{
	t_sprite	*cur;

	cur = s->sprite;
	while (cur != NULL)
	{
		if (cur->anim.image[cur->current] != NULL)
		{
			if (cur->life == 0)
				kill(cur);
			// else if (cur->r_dist <= SPRITE_SHOT_DIST)
			// 	sprite_shooting(s, cur);
			else
			{
				// ia(s, cur);
				// set_orientation(s, cur);
				// sprite_orientation(s);
				// sprite_walk(cur);
			}
		}
		else
			cur->current = 0;
		cur = cur->next;
	}
}

int			calc_angle(double angle, int range)
{
	int		ret;

	ret = (angle + range);
	if (ret > 360)
		ret = ret - 360;
	if (ret < 0)
		ret = 360 + ret;
	return (ret);
}

// void		set_img(t_main *s, t_sprite *cur, int id, int orientation)
// {
// 	t_lsprite	*lst;
// 	int			i;
//
// 	i = -1;
// 	lst = s->lsprite;
// 	while (++i != id && lst != NULL)
// 		lst = lst->next;
// //	printf("id = %d\n",lst->id);
// 	// printf("current = %d\n",lst->anim->current);
// 	if (lst->anim != NULL)
// 	{
// 		cur->orientation = orientation;
// 		// cur->anim = lst->anim;
// 		// cur->img = lst->anim->image[cur->current];
// 	}
// }

void		set_orientation(t_main *s, t_sprite *cur)
{
	// int		i;
	// int		angle;
	//
	// i = -1;
	// while (++i != 360)
	// {
	// 	angle = calc_angle(cur->s_angle, i);
	// 	if (angle == (int)s->player.angle)
	// 		break ;
	// }
	// if ((i >= 0 && i <= 22) || (i >= 337 && i <= 360))
	// 	set_img(s, cur, 1, 0);
	// if (i >= 23 && i <= 67)
	// 	set_img(s, cur, 3, 1);
	// if (i >= 68 && i <= 112)
	// 	set_img(s, cur, 2, 1);
	// if (i >= 113 && i <= 157)
	// 	set_img(s, cur, 4, 1);
	// if (i >= 158 && i <= 202)
	// 	set_img(s, cur, 0, 0); //face
	// if (i >= 203 && i <= 247)
	// 	set_img(s, cur, 4, 0);
	// if (i >= 248 && i <= 292)
	// 	set_img(s, cur, 2, 0);
	// if (i >= 293 && i <= 337)
	// 	set_img(s, cur, 3, 0);
}
