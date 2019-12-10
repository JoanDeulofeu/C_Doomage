#include "doom.h"

void 	select_sprite_in_menu(t_main *s)
{
	t_name	name;
	t_name	max_name;
	t_pos	pos;
	t_image *img;

	if (s->editor->sprite_menu.current == 0)
	{
		name = storm;
		max_name = storm;
	}
	else if (s->editor->sprite_menu.current == 1)
	{
		name = table;
		max_name = table;
	}
	else
	{
		name = storm;
		max_name = storm;
	}
	while (name <= max_name)
	{
		pos = s->editor->m_sprite_pos[name];
		img = s->editor->all_sprite.image[name];
		if (s->ft_mouse.x > pos.x && s->ft_mouse.x < pos.x + img->w
		&& s->ft_mouse.y > pos.y && s->ft_mouse.y < pos.y + img->h)
		{
			s->editor->sprite_selected = name;
			break ;
		}
		name++;
	}
}

void 	draw_plain_sprite(t_main *s, t_pos coord, t_image *img)
{
	double		perx;
	double		pery;
	t_pos		ori;
	int			px;
	int 		i;
	int			j;

	ori = coord;
	i = 0;
	while (i < img->w)
	{
		j = 0;
		coord.x = ori.x + i;
		perx = (double)i / (double) img->w;
		while (j < img->h)
		{
			coord.y = ori.y + j;
			pery = (double)j / (double) img->h;
			px = (int)(pery * (double)img->h) * img->w +
			(int)(perx * (double)img->w);
			if (px >= 0 && px < img->w * img->h)
				set_pixel(s->sdl->editor, img->tex[px], coord);
			j++;
		}
		i++;
	}
}

void 	draw_sprite_list(t_main *s)
{
	t_name	name;
	// printf("select sprite = %d\n", s->editor->select_sprite);
	if (s->editor->sprite_menu.current == 0)
	{
		name = storm;
		while (name < table)
		{
			draw_plain_sprite(s, s->editor->m_sprite_pos[name], s->editor->all_sprite.image[name]);
			name++;
		}
	}
	else if (s->editor->sprite_menu.current == 1)
	{
		name = table;
		while (name <= table)
		{
			draw_plain_sprite(s, s->editor->m_sprite_pos[name], s->editor->all_sprite.image[name]);
			name++;
			// printf("%d\n", name);
		}
	}
}

void 	select_sprite_type(t_main *s)
{
	t_image	*img;
	t_pos	begin;
	t_pos	end;

	img = s->editor->sprite_menu.image[0];
	begin.x = WIDTH / 2 - img->w / 2;
	begin.y = HEIGHT / 2 - img->h / 2;
	end.x = begin.x + img->w;
	end.y = begin.y + img->h;
	if (s->ft_mouse.x >= begin.x && s->ft_mouse.x <= begin.x + 200)
	{
		if (s->ft_mouse.y >= begin.y && s->ft_mouse.y <= begin.y + 60)
		{
			s->editor->sprite_menu.current = 0;

		}
		else if (s->ft_mouse.y > 60 && s->ft_mouse.y <= begin.y + 120)
			s->editor->sprite_menu.current = 1;
		else if (s->ft_mouse.y > 120 && s->ft_mouse.y <= begin.y + 180)
			s->editor->sprite_menu.current = 2;
	}
	if (s->ft_mouse.x > begin.x + 200 && s->ft_mouse.x < end.x
		&& s->ft_mouse.y > begin.y && s->ft_mouse.y < end.y)
			select_sprite_in_menu(s);
}

void 	display_sprite_menu(t_main *s)
{
	double		perx;
	double		pery;
	t_pos		coord;
	t_pos		ori;
	int			px;
	t_anim		menu;
	int 		i;
	int			j;


	menu = s->editor->sprite_menu;
	coord.x = WIDTH / 2 - menu.image[0]->w / 2;
	coord.y = HEIGHT / 2 - menu.image[0]->h / 2;
	ori = coord;
	i = 0;

	while (i < menu.image[0]->w)
	{
		j = 0;
		coord.x = ori.x + i;
		perx = (double)i / (double) menu.image[0]->w;
		while (j < menu.image[0]->h)
		{
			coord.y = ori.y + j;
			pery = (double)j / (double) menu.image[0]->h;
			px = (int)(pery * (double)menu.image[menu.current]->h) * menu.image[menu.current]->w + (int)
			(perx * (double)menu.image[menu.current]->w);
			if (px >= 0 && px < menu.image[menu.current]->w * menu.image[menu.current]->h)
				set_pixel(s->sdl->editor, menu.image[menu.current]->tex[px], coord);
			j++;
		}
		i++;
	}
	ori.x += 200;
	draw_sprite_list(s);
}

void	remove_sprite_from_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*temp;
	t_lsprite	*del;

	sct = get_sector_by_id(s, sprite->sct_id);
	temp = sct->liste;
	// printf("sprite a supprimer = %d\n", sprite->id);
	// printf("secteur du sprite a supprimer = %d\n", sct->id);
	// ft_print_sectors_sprites(s);

	if (!temp)
		return ;
	if (temp->sprite->id == sprite->id)
	{
		sct->liste = temp->next;
		// ft_memdel((void *)temp);
		free(temp);
		temp = NULL;
	}

	else
	{
		while (temp->next->sprite->id != sprite->id)
			temp = temp->next;
		del = temp->next;
		temp->next = temp->next->next;
		free(del);
		del = NULL;
		// ft_memdel((void *)del);
	}

}

void	remove_sprite(t_main *s, int id)
{
	t_sprite	*temp;
	t_sprite	*sprite;

	temp = s->sprite;
	if (temp->id == id)
	{
		s->sprite = temp->next;
		remove_sprite_from_sector(s, temp);
		// ft_memdel((void *)&temp);
		free(temp);
		temp = NULL;
		// s->sprite = NULL;
		return ;
	}
	while (temp->next)
	{
		if (temp->next->id == id)
		{
			sprite = temp->next;
			remove_sprite_from_sector(s, sprite);
			temp->next = sprite->next;
			// ft_memdel((void *)&sprite);
			free(sprite);
			sprite = NULL;
			return ;
		}
		temp = temp->next;
	}
}

void	remove_selected_sprite(t_main *s)
{
	t_sprite	*sprite;

	sprite = s->sprite;
	while (sprite)
	{
		if (sprite->selected == 1)
		{
			// printf("sprite a supprimer %d\n", sprite->id);
			remove_sprite(s, sprite->id);
			deselect_sprite(s);
			// ft_print_sectors_sprites(s);
			return ;
		}
		sprite = sprite->next;
	}
}

void 		draw_sprites_ori(t_main *s)
{
	t_sprite	*tmp;
	t_dpos		pos;

	tmp = s->sprite;
	while (tmp)
	{
		pos.x = tmp->r_ori.x * METRE;
		pos.y = tmp->r_ori.y * METRE;
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, pos)), YELLOW);
		tmp = tmp->next;
	}
}

void 		add_sprite_to_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*tmp;
	t_lsprite	*liste;

	sct = get_sector_by_id(s, sprite->sct_id);
	if ((liste = malloc(sizeof(t_lsprite))) == NULL)
		handle_error(s, MALLOC_ERROR);
	liste->sprite = sprite;
	liste->next = NULL;
	if (sct->liste == NULL)
		sct->liste = liste;
	else
	{
		tmp = sct->liste;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = liste;
	}
	// ft_print_sectors_sprites(s);
}

t_sprite	*create_new_sprite(t_main *s, t_type type, t_dpos r_pos)
{
	t_sprite	*sprite;
	t_sprite	*temp;
	int			sct_id;
	t_dpos		pos;

	sprite = NULL;
	pos = ft_pos_to_dpos(get_px_r_pos(s, r_pos));
	if ((sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos))) == 0)
		return (NULL);
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->sct_id = ft_is_in_sector(s, ft_dpos_to_pos(pos));
	sprite->r_pos = r_pos;
	sprite->size = 2;
	sprite->pos = ft_dpos_to_pos(pos);
	sprite->r_ori = sprite->r_pos;
	sprite->m_pos.x = sprite->r_pos.x * METRE;
	sprite->m_pos.y = sprite->r_pos.y * METRE;
	sprite->type = type;
	sprite->life = 100;
	sprite->set = 0;
	sprite->anim = s->stormtrooper.face;
	if (!s->sprite)
	{
		s->sprite = sprite;
		s->sprite->id = 1;
		add_sprite_to_sector(s, sprite);
		return (sprite);
	}
	temp = s->sprite;
	while (temp->next)
		temp = temp->next;
	temp->next = sprite;
	sprite->id = temp->id + 1;
	add_sprite_to_sector(s, sprite);
	return (sprite);
}
