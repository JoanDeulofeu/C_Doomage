#include "doom.h"

t_pos		get_subline_coord(t_main *s, t_name value)
{
	t_pos	new;
	t_name	name;

	new.x = WIDTH / 2 - s->editor->sprite_menu.image[0]->w / 2 + 205;;
	new.y = 0;
	name = 0;
	if (value < table) //si on est sur les enemeis
		name = storm;
	else if (value < o_gun) // a changer quand il y a plusieurs obstacles
		name = table;
	else if (value <= big_s_ammo)
		name = o_gun;
	while (name < value)
	{
		if (new.y < s->editor->m_sprite_pos[name].y)
			new.y = s->editor->m_sprite_pos[name].y;
		name++;
	}
	return (new);
}

void 		fill_sprite_list_value(t_main *s)
{
	t_name	name;
	t_pos	coord;
	t_pos	end;

	coord.x = WIDTH / 2 - s->editor->sprite_menu.image[0]->w / 2 + 205;
	coord.y = HEIGHT / 2 - s->editor->sprite_menu.image[0]->h / 2 + 5;
	end.x = coord.x + s->editor->sprite_menu.image[0]->w;
	end.y = coord.y + s->editor->sprite_menu.image[0]->h;
	// printf("select sprite = %d\n", s->editor->select_sprite);
	name = storm;
	while (name <= big_s_ammo)
	{
		if (name == storm || name == table || name == o_gun)
		{
			coord.x = WIDTH / 2 - s->editor->sprite_menu.image[0]->w / 2 + 205;
			coord.y = HEIGHT / 2 - s->editor->sprite_menu.image[0]->h / 2 + 5;
		}
		if (coord.x + s->editor->all_sprite.image[name]->w < end.x)
			s->editor->m_sprite_pos[name] = coord;
		else
			s->editor->m_sprite_pos[name] = get_subline_coord(s, name);
		coord.x += s->editor->all_sprite.image[name]->w + 5;
		name++;

	}
}

void		pre_initialize_sdl(t_main *s)
{
	if (!(s->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		exit(-1);
	s->sdl->pwindow = NULL;
	s->sdl->prenderer = NULL;
	s->sdl->map = NULL;
	s->sdl->game = NULL;
	s->sdl->musique = NULL;
	s->sdl->editor = NULL;
}

void		initialize_editor(t_editor *edi)
{
	ft_bzero((void *)edi, sizeof(t_editor));
	edi->space = G_SPACE;
	edi->anchor_size = 5;
	edi->mode = move;
	edi->decal_x = 0;
	edi->decal_y = 0;
	edi->ref.x = 0;
	edi->ref.y = 0;
	edi->color_sector = 2;
	edi->dply_floor = 0;
	edi->mode_floor = 0;
	edi->portal_temp = 0;
	edi->selected = 0;
	edi->over_portal = 0;
	edi->over_sector = 0;
	edi->over_sector2 = 0;
	edi->wall = NULL;
	edi->wall2 = NULL;
}

void		initialize_sdl(t_main *s, t_sdl *sdl)
{
	(void)s;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
	if (TTF_Init() == -1)
		ft_error_ttf("Erreur initialisation TTF_Init: ");
	if (!(sdl->pwindow = SDL_CreateWindow("Doom Nukem", 100,
		100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		ft_error_sdl("Échec de creation de la fenetre");
	if (!(sdl->prenderer = SDL_CreateRenderer(sdl->pwindow, -1, 0)))
		ft_error_sdl("Échec de chargement du renderer");
	// load_images(s);
	// s->weapon.current = 0;
	// if (check_images(s) == 0)
	// 	exit(-1);
	if (!(sdl->map = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	if (!(sdl->game = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	if (!(sdl->editor = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	if (!(sdl->save = initialize_texture(sdl, WIDTH, HEIGHT)))
		exit(-1);
	// sdl->x_o = WIDTH / 2 - ((SPACE * s->width) / 2);
	// sdl->y_o = HEIGHT / 2 - ((SPACE * s->height) / 2);
	sdl->musique = NULL;
	create_sounds(sdl);
	// if (s->interface->h > HEIGHT * 0.3)
	// 	s->interface->h = HEIGHT * 0.3;
	// if (s->interface->h > WIDTH)
	// 	s->interface->w = WIDTH;
	ft_init_font(s);
	// if (s->interface->h > HEIGHT * 0.3)
	// 	s->interface->h = HEIGHT * 0.3;
	// if (s->interface->h > WIDTH)
	// 	s->interface->w = WIDTH;
}

void		load_images(t_main *s)
{
	int	i;

	i = 0;
	while (i < 18)
	{
		s->editor->menu.image[i] = NULL;
		s->player.weapon.image[i] = NULL;
		s->editor->m_floor.image[i] = NULL;
		s->menu.image[i] = NULL;
		s->editor->sprite_menu.image[i] = NULL;
		s->skybox.image[i] = NULL;
		s->editor->all_sprite.image[i++] = NULL;
	}
	s->editor->menu.image[0] = load_tga("images/move.tga", 0, 0, 0);
	s->editor->menu.image[1] = load_tga("images/vertex.tga", 0, 0, 0);
	s->editor->menu.image[2] = load_tga("images/sector.tga", 0, 0, 0);
	s->editor->menu.image[3] = load_tga("images/player.tga", 0, 0, 0);
	s->editor->menu.image[4] = load_tga("images/portal.tga", 0, 0, 0);
	s->editor->menu.image[5] = load_tga("images/save.tga", 0, 0, 0);
	s->editor->sprite_menu.image[0] = load_tga("images/ressources/sprite_menu/sprite_01.tga", 0, 0, 0);
	s->editor->sprite_menu.image[1] = load_tga("images/ressources/sprite_menu/sprite_02.tga", 0, 0, 0);
	s->editor->sprite_menu.image[2] = load_tga("images/ressources/sprite_menu/sprite_03.tga", 0, 0, 0);
	s->editor->sprite_menu.current = 0;
	s->editor->m_floor.image[0] = load_tga("images/stage.tga", 0, 0, 0);
	s->editor->m_floor.image[1] = load_tga("images/s_enabled.tga", 0, 0, 0);

	s->menu.image[0] = load_tga("images/menu.tga", 0, 0, 0);
	s->menu.image[1] = load_tga("images/play.tga", 0, 0, 0);
	s->menu.image[2] = load_tga("images/editor.tga", 0, 0, 0);
	s->menu.current = 0;
	s->savemap->croix_rouge = load_tga("images/croix_rouge.tga", 0, 0, 0);
	s->player.hud = load_tga("images/hud_doom.tga", 0, 0, 0);
	s->player.crosshair = load_tga("images/crosshair.tga", 0, 0, 0);
	load_anims(s);
	fill_sprite_list(s);
	fill_sprite_list_value(s);
	fill_texture_list(s);

	s->skybox.current = 0;
	s->player.mun_gun = 45;
	s->player.mun_shotgun = 12;
	s->player.weapon = s->wp_anims.kick;
	s->player.wp_name = kick;
	s->player.wp_wheel[gun] = 0;
	s->player.wp_wheel[kick] = 1;
	s->player.wp_wheel[shotgun] = 0;
	s->player.weapon.current = 0;
	//s->sprites.img = load_tga("images/shotgun1.tga", 0, 0, 0);
	s->editor->menu.current = 0;
	s->editor->m_floor.current = 0;
	// s->lsprite = create_lsprite(s, 7);
}

t_texture	*initialize_texture(t_sdl *sdl, int width, int height)
{
	t_texture	*text;

	if (!(text = (t_texture *)malloc(sizeof(t_texture))))
		return (NULL);
	if (!(text->content = (Uint32 *)malloc(width * height * sizeof(Uint32))))
		return (NULL);
	if (!(text->texture = SDL_CreateTexture(sdl->prenderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height)))
		return (NULL);
	text->color_tmp = 0xFFFFFFFF;
	return (text);
}

t_main		*initialize_main(char *str)
{
	t_main		*s;

	if (!(s = (t_main*)malloc(sizeof(t_main))))
		exit(-1);
	ft_bzero((void*)s, sizeof(t_main));
	if (!(s->editor = (t_editor*)malloc(sizeof(t_editor))))
		exit(-1);
	if (!(s->font = (t_font*)malloc(sizeof(t_font))))
		exit(-1);
	if (!(s->savemap = (t_savemap*)malloc(sizeof(t_savemap))))
		exit(-1);
	if (!(s->time = (t_timer*)malloc(sizeof(t_timer))))
		exit(-1);
	if (!(s->msg = (t_msg*)malloc(sizeof(t_msg))))
		exit(-1);
	if (str)
		s->map_name = ft_strdup(str);
	else
		s->map_name = ft_strdup(MAP);
	ft_bzero(s->savemap->str, 41);
	ft_bzero((void *)s->editor, sizeof(t_editor));
	s->savemap->error_msg = 0;
	initialize_editor(s->editor);
	s->vertex = NULL;
	s->sector = NULL;
	s->grid = NULL;
	s->sprite = NULL;
	ft_set_time(s);
	ft_init_msg(s);
	s->player.shoot = 0;
	s->player.set = 1;
	s->player.size = PLAYER_SIZE;
	s->player.jump = 0;
	s->player.jump_height = 0;
	s->player.fly = 0;
	s->player.tumble = 0.0;
	s->player.i = 0;
	s->player.r_pos.x = 7.5;
	s->player.r_pos.y = 7.3;
	s->player.m_pos.x = s->player.r_pos.x * METRE;
	s->player.m_pos.x = s->player.r_pos.y * METRE;
	s->player.health = 100;
	s->player.armor = 100;
	s->player.keys = 0;

	// s->sprite.damage = 1;

	s->ennemi.damage = -1;
	//
	s->object.health_pack = 20;

	s->player.eyesight = EYESIGHT;
	s->player.y_eye = 0;

	s->tmp_intersect.x = 0;
	s->tmp_intersect.y = 0;
	s->intersect1.x = 0;
	s->intersect1.y = 0;
	s->intersect2.x = 0;
	s->intersect2.y = 0;
	s->play_or_editor = 2;

	s->player.abs_angle = 180;
	s->player.angle = s->player.abs_angle;
	s->player.sector_id = 0;
	s->player.sector = NULL;
	s->display_mode = 0;
	s->player.init_space = s->editor->space;
	s->str_vtx = NULL;
	s->walls = NULL;
	s->portal_nb = 0;
	s->interface = NULL;
	s->sprite = NULL;
	pre_initialize_sdl(s);
	initialize_sdl(s, s->sdl);
	load_images(s);
	// init_sprite(s);
	s->save_coord_vtx.x = 0;
	s->save_coord_vtx.y = 0;

	return (s);
}
