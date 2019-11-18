#include "doom.h"

void		load_lanim(t_lanim *data, t_name name)
{
	// if (idanim == 1)
	// 	load_anim1(data);
	// if (idanim == 2)
	// 	load_anim2(data);
	// if (idanim == 3)
	// 	load_anim3(data);
	// if (idanim == 4)
	// 	load_anim4(data);
	// if (idanim == 5)
	// 	load_anim5(data);
	// if (idanim == 6)
	// 	load_anim6(data);
	// if (idanim == 7)
	// 	load_anim7(data);
}

// t_lanim		*create_lanim_elem(t_main *s, int id, int idanim)
// {
// 	t_lanim	*data;
//
// 	data = NULL;
// 	if (!(data = ft_memalloc(sizeof(t_lanim))))
// 		handle_error(s, MALLOC_ERROR);
// 	data->id = id;
// 	data->max_current = 15;
// 	load_lanim(data, idanim);
// 	return (data);
// }
// 
// t_lsprite	*load_lsprite(t_main *s, t_lsprite *start, int size)
// {
// 	t_lsprite	*cur;
// 	int			i;
//
// 	i = -1;
// 	cur = start;
// 	while (++i < size)
// 	{
// 		cur->anim = create_lanim_elem(s, i, (i + 1));
// 		cur = cur->next;
// 	}
// 	return (start);
// }
//
// t_lsprite	*create_lsprite_elem(t_main *s, int id)
// {
// 	t_lsprite	*data;
//
// 	data = NULL;
// 	if (!(data = ft_memalloc(sizeof(t_lsprite))))
// 		handle_error(s, MALLOC_ERROR);
// 	data->id = id;
// 	data->img = NULL;
// 	data->anim = NULL;
// 	data->next = NULL;
// 	return (data);
// }
//
// t_lsprite	*create_lsprite(t_main *s, int size)
// {
// 	t_lsprite	*new;
// 	t_lsprite	*start;
// 	int			i;
//
// 	i = 0;
// 	new = create_lsprite_elem(s, i);
// 	start = new;
// 	while (++i < size)
// 	{
// 		new->next = create_lsprite_elem(s, i);
// 		new = new->next;
// 	}
// 	start = load_lsprite(s, start, size);
// 	return (start);
// }
