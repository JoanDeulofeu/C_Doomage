#include "doom.h"

void	pre_initialize_sdl(t_main *s)
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

void		initialize_sdl(t_main *s, t_sdl *sdl)
{
	(void)s;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		ft_error_sdl("Échec de l'initialisation de la SDL");
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
	// sdl->x_o = WIDTH / 2 - ((SPACE * s->width) / 2);
	// sdl->y_o = HEIGHT / 2 - ((SPACE * s->height) / 2);
	sdl->musique = NULL;
	// create_sounds(sdl);
	// if (s->interface->h > HEIGHT * 0.3)
	// 	s->interface->h = HEIGHT * 0.3;
	// if (s->interface->h > WIDTH)
	// 	s->interface->w = WIDTH;
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

t_main		*initialize_main(void)
{
	t_main	*s;

	if (!(s = (t_main *)malloc(sizeof(t_main))))
		exit(-1);
	s->vertex = NULL;
	s->sector = NULL;
	s->grid = NULL;
	// s->mouse.x = 0;
	// s->mouse.y = 0;
	pre_initialize_sdl(s);
	initialize_sdl(s, s->sdl);
	return (s);
}
