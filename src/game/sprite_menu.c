// #include "doom.h"
// #define WIDTH_SPRITE 35
// #define HEIGHT_SPRITE 70
//
// void		display_img(t_main *s, int x, int y, t_image *img)
// {
// 	double	perx;
// 	double	pery;
// 	t_pos	coord;
// 	int		px;
// 	t_image	*wp;
// 	int		i;
// 	int		j;
//
// 	coord.x = 0;
// 	coord.y = 0;
// 	wp = img;
// 	i = 0;
// 	while (i < wp->w)
// 	{
// 		j = 0;
// 		coord.x = i;
// 		perx = (double)coord.x / (double)wp->w;
// 		coord.x += x;
// 		while (j < wp->h)
// 		{
// 			coord.y = j++;
// 			pery = (double)coord.y / (double)wp->h;
// 			coord.y += y;
// 			px = (int)(pery * (double)wp->h) * wp->w +
// 				(int)(perx * (double)wp->w);
// 			if (px >= 0 && px < wp->w * wp->h)// && wp->tex[px] != 10676224)
// 			{
// 				set_pixel(s->sdl->editor, wp->tex[px], coord);
// 			}
// 		}
// 		i++;
// 	}
// }
//
// void		draw_sprite_menu(t_main *s)
// {
// 	t_lsprite	*cur;
// 	int			x;
// 	int			y;
//
// 	cur = s->lsprite;
// 	x = WIDTH - WIDTH_SPRITE;
// 	y = 0;
// 	while (cur != NULL)
// 	{
// 		//printf("w, h(%d, %d)\n", cur->img->w, cur->img->h);
// 		display_img(s, x, y, cur->img);
// 		cur = cur->next;
// 		y += HEIGHT_SPRITE + 1;
// 	}
// }
//
// int			check_sprite_menu_click(t_main *s, t_pos pos)
// {
// 	t_lsprite	*lst;
// 	int			end;
// 	int			max;
//
// 	max = 0;
// 	lst = s->lsprite;
// 	while (lst != NULL)
// 	{
// 		max++;
// 		lst = lst->next;
// 	}
// 	end = HEIGHT_SPRITE * max + max;
// 	if ((pos.x < (WIDTH - WIDTH_SPRITE)) || (pos.y > end))
// 		return (-1);
// 	end = end / max;
// 	lst = s->lsprite;
// 	while (lst != NULL)
// 	{
// 		if (pos.y < end)
// 			s->choice_sprite = lst;
// 		return (s->choice_sprite->id);
// 		end += end;
// 		lst = lst->next;
// 	}
// 	return (-1);
// }
//
// // void display_menu_sprite(t_main *s)
// // {
// //   t_pos start;
// //   t_pos end;
// //   t_pos cur;
// //
// //   start.x = WIDTH - WIDTH_SPRITE;
// //   start.y = 0;
// //   end.x = WIDTH;
// //   end.y = HEIGHT;
// //   cur.x = start.x;
// //   while (cur.x != end.x)
// //   {
// //     cur.y = start.y;
// //     while (cur.y != end.y)
// //     {
// //       set_pixel(s->sdl->editor, BLACK, cur);
// //       cur.y++;
// //     }
// //     cur.x++;
// //   }
// //   draw_menu_img(s);
// // 	// if (s->choice_sprite != NULL)
// // 	//
// //
// // 		//printf("id = %d\n",s->choice_sprite->id);
// // }
