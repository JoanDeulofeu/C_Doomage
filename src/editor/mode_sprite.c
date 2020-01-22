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
		max_name = lamp;
	}
	else
	{
		name = o_gun;
		max_name = big_s_ammo;
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

void 	draw_plain_sprite(t_main *s, t_pos coord, t_image *img, t_texture *tex)
{
	double		perx;
	double		pery;
	t_pos		ori;
	int			px;
	int 		i;
	int			j;

	(void)s;
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
				set_pixel(tex, img->tex[px], coord);
			j++;
		}
		i++;
	}
}

void 	draw_selected_feedback(t_main *s, t_name name, t_pos pos)
{
	t_dpos	ori;
	t_dpos	dest;

	ori.x = pos.x - 5;
	ori.y = pos.y - 5;
	dest.x = pos.x + s->editor->all_sprite.image[name]->w + 5;
	dest.y = pos.y + s->editor->all_sprite.image[name]->h + 5;
	draw_rect(s->sdl->editor, ori, dest, GREEN);
}

void 	draw_sprite_list(t_main *s)
{
	t_name	name;
	if (s->editor->sprite_menu.current == 0)
	{
		name = storm;
		while (name < table)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(s, s->editor->m_sprite_pos[name], s->editor->all_sprite.image[name], s->sdl->editor);
			name++;
		}
	}
	else if (s->editor->sprite_menu.current == 1)
	{
		name = table;
		while (name <= lamp)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(s, s->editor->m_sprite_pos[name], s->editor->all_sprite.image[name], s->sdl->editor);
			name++;
			// printf("%d\n", name);
		}
	}
	else if (s->editor->sprite_menu.current == 2)
	{
		name = o_gun;
		while (name <= big_s_ammo)
		{
			if (s->editor->sprite_selected == name)
				draw_selected_feedback(s, name, s->editor->m_sprite_pos[name]);
			draw_plain_sprite(s, s->editor->m_sprite_pos[name], s->editor->all_sprite.image[name], s->sdl->editor);
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
	// ori.x += 200;
	draw_sprite_list(s);
}

void	remove_sprite_from_sector(t_main *s, t_sprite *sprite)
{
	t_sector	*sct;
	t_lsprite	*temp;
	t_lsprite	*del;

	sct = get_sector_by_id(s, sprite->sct_id);
	if (!sct)
		return ;
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
	Uint32		color;

	tmp = s->sprite;
		while (tmp)
	{
		if (tmp->type == enemy)
			color = YELLOW;
		else if (tmp->type == obstacle)
			color = S_RED;
		else
			color = S_PINK;
		pos.x = tmp->r_ori.x * METRE;
		pos.y = tmp->r_ori.y * METRE;
		draw_anchor(s, ft_dpos_to_pos(to_edi_coord(s, pos)), color);
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

void 		get_sprite_info_by_name(t_main *s, t_name name, t_sprite *sprite)
{
	if (name != none)
		sprite->name = name;
	else
		sprite->name = s->editor->sprite_selected;
	if (sprite->name == storm)
	{
		sprite->size = 2;
		sprite->anim = s->stormtrooper.face;
		sprite->type = enemy;
	}
	else if (sprite->name == table)
	{
		sprite->size = 1;
		sprite->anim = s->items.table;
		sprite->type = obstacle;
	}
	else if (sprite->name == lamp)
	{
		sprite->size = 3;
		sprite->anim = s->items.lamp;
		sprite->type = obstacle;
	}
	else if (sprite->name == o_gun)
	{
		sprite->size = 0.5;
		sprite->anim = s->items.gun;
		sprite->type = item;
	}
	else if (sprite->name == o_shotgun)
	{
		sprite->size = 0.3;
		sprite->anim = s->items.shotgun;
		sprite->type = item;
	}
	else if (sprite->name == big_g_ammo)
	{
		sprite->size = 0.2;
		sprite->anim = s->items.big_g_ammo;
		sprite->type = item;
	}
	else if (sprite->name == big_s_ammo)
	{
		sprite->size = 0.2;
		sprite->anim = s->items.big_s_ammo;
		sprite->type = item;
	}
	else if (sprite->name == jetpack)
	{
		sprite->size = 0.5;
		sprite->anim = s->items.jetpack;
		sprite->type = item;
	}
}

t_sprite	*create_new_sprite(t_main *s, t_name name, t_dpos r_pos)
{
	t_sprite	*sprite;
	t_sprite	*temp;
	int			sct_id;
	t_dpos		pos;

	sprite = NULL;
	pos.x = r_pos.x * METRE;
	pos.y = r_pos.y * METRE;
	 //pos = ft_pos_to_dpos(get_px_r_pos(s, r_pos));
	if ((sct_id = ft_is_in_sector(s, pos)) == 0)
		return (NULL);
	if (!(sprite = ft_memalloc(sizeof(t_sprite))))
		handle_error(s, MALLOC_ERROR);
	ft_bzero((void*)sprite, sizeof(t_sprite));
	sprite->sct_id = ft_is_in_sector(s, pos);
	sprite->r_pos = r_pos;
	sprite->r_dist = 100;
	sprite->pos = get_px_r_pos(s, r_pos);
	sprite->r_ori = sprite->r_pos;
	sprite->m_pos = pos;
	sprite->life = 100;
	sprite->set = 0;
	get_sprite_info_by_name(s, name, sprite);

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
