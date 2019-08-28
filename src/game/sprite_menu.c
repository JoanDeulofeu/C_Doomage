#include "doom.h"

void display_img(t_main *s, int x, int y, t_image *img)
{
	double		perx;
	double		pery;
	t_pos		coord;
	int			px;
	t_image		*wp;
  int i;
  int j;

	coord.x = 0;
	coord.y = 0;
	wp = img;
	//coord.x = WIDTH / 2 - (wp->w / 2);
  i = 0;
	while (i < wp->w)
	{
		j = 0;//dont touch
		coord.x = i ;

		perx = (double)coord.x / (double)wp->w;
		coord.x += x;
    // printf("h = %d\n", wp->h);
		while (j < wp->h)
		{
			coord.y = j++;
			pery = (double)coord.y / (double)wp->h;
			coord.y += y;
			px = (int)(pery * (double)wp->h) * wp->w + (int)(perx * (double)wp->w);
			if (px >= 0 && px < wp->w * wp->h && wp->tex[px] != 10676224)
				set_pixel(s->sdl->editor, wp->tex[px], coord);
		}
		i++;
	}
}


void draw_menu_img(t_main *s)
{
  t_lsprite *cur;
  int x;
  int y;


  cur = s->lsprite;
  x= 800;
  y = 0;
  while (cur != NULL)
  {
    if (x > 900 )
    {
      x = 800;
      y += 100;
    }
    display_img(s,x,y,cur->img);

    cur = cur->next;
    x +=100;
  }
  // display_img(s,900,0);
}

void display_menu_sprite(t_main *s)
{
  t_pos start;
  t_pos end;
  t_pos cur;

  start.x = 800;
  start.y = 0;
  end.x = 1000;
  end.y = 400;
  cur.x = start.x;
  while (cur.x != end.x)
  {
    cur.y = start.y;
    while (cur.y != end.y)
    {
      set_pixel(s->sdl->editor, BLACK, cur);
      cur.y++;
    }
    cur.x++;
  }
  draw_menu_img(s);
}
