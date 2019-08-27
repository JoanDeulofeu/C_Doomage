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


t_lsprite 				*load_lsprite(t_main *s, t_lsprite *start)
{
	t_lsprite *cur;

	cur = start;
	cur->img = load_tga("images/shotgun1.tga", 0, 0, 0);
	cur = cur->next;
	cur->img = load_tga("images/shotgun_fire2.tga", 0, 0, 0);
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
		start = load_lsprite(s,start);
		return (start);
}


void             init_sprite(t_main *s)
{
  t_sprite   *tmp;
  t_dpos      pos;

  pos.x = 300;
  pos.y = 200;
  s->sprite = create_sprite_elem(s,0,0,pos);
  pos.x = 400;
  pos.y = 300;
  add_sprite(s,pos,1);


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
	data->pos = pos;
	data->id  = id;
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
