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
	(void)s;
	(void)cur;
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
