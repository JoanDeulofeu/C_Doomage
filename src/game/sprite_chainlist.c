#include "doom.h"

void	*ft_memalloc(size_t size)
{
	void *ptr;

	ptr = (void *)malloc(sizeof(void *) * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}

void             init_sprite(t_main *s)
{
  t_dpos      r_pos;

  r_pos.x = 12.5;
  r_pos.y = 6.5;
  s->sprite = create_sprite_elem(s,0,0,r_pos);
  r_pos.x = 7.5;
  r_pos.y = 4.2;
  add_sprite(s,r_pos,1);
  r_pos.x = 13;
  r_pos.y = 10;
  add_sprite(s,r_pos,2);

}

double      calc_sprite_dist(t_main *s, t_pos pos)
{
  t_dpos distance;
  double dist;

  distance.x =  pos.x - s->player.pos.x;
  distance.y =  pos.y - s->player.pos.y;
  dist = (distance.x * distance.x) + (distance.y * distance.y);
  dist = sqrt(dist);
  return (dist);
}

void        refresh_sprite_pos(t_main *s)
{
  t_sprite *cur;

  cur = s->sprite;
  while (cur != NULL)
  {
    cur->pos = get_px_r_pos(s,cur->r_pos);
    cur->dist = calc_sprite_dist(s,cur->pos);
    cur->set = 0;
    cur->angle = 0;
    draw_anchor(s,cur->pos, YELLOW);
    cur = cur->next;
  }
}


t_lsprite 				*load_lsprite(t_lsprite *start)
{
	t_lsprite *cur;

	cur = start;
	cur->img = load_tga("images/trooper_face01.tga", 0, 0, 0);
	cur = cur->next;
	cur->img = load_tga("images/trooper_face01.tga", 0, 0, 0);
  cur = cur->next;
  cur->img = load_tga("images/trooper_face01.tga", 0, 0, 0);
	return (start);
}

t_lsprite 		*create_lsprite_elem(t_main *s, int id)
{
	t_lsprite	*data;

	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_lsprite))))
		handle_error(s, MALLOC_ERROR);
	data->id  = id;
	data->img = NULL;
	data->anim = NULL;
	data->next = NULL;
	return (data);
}

t_lsprite 		*create_lsprite(t_main *s, int size)
{
		t_lsprite *new;
		t_lsprite *start;
		int 			i;

		i = 0;
		new = create_lsprite_elem(s,i);
		start = new;
		while (++i < size)
		{
			new->next = create_lsprite_elem(s,i);
			new = new->next;
		}
		start = load_lsprite(start);
		return (start);
}





t_sprite 		*create_sprite_elem(t_main *s, int id, int idimg, t_dpos pos)
{
	t_sprite	*data;
	t_lsprite *lst;
	int i;

	i = -1;
	lst = s->lsprite;
	data = NULL;
	if (!(data = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	data->r_pos = pos;
  data->pos = get_px_r_pos(s,pos);
  data->id = id;
  data->set = 0;
  data->angle = 0;
	data->dist  = calc_sprite_dist(s,data->pos);
	data->img = NULL;
	data->anim = NULL;
	data->next = NULL;
	while (++i != idimg)
		lst = lst->next;
	if (lst->img == NULL)
		data->anim = lst->anim;
	else
		data->img = lst->img;
	return (data);
}

void	add_sprite(t_main *s, t_dpos pos, int idimg)
{
	t_sprite *tmp;

	tmp = s->sprite;
	while (tmp->next != NULL)
	 	tmp = tmp->next;
	tmp->next = create_sprite_elem(s,(tmp->id+1),idimg,pos);
}
