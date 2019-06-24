/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:10:18 by ydonse            #+#    #+#             */
/*   Updated: 2019/06/24 15:43:02 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include "libft.h"
# include <SDL.h>
# include <SDL_mixer.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# define WIDTH 1000 //multiple de 20
# define HEIGHT 800 //multiple de 20

# define FILE_ERROR 1
# define SIZE_ERROR 2
# define SYNTAX_ERROR 3
# define MALLOC_ERROR 4
# define PLAYER_ERROR 5
# define WALL_ERROR 6

# define LEFT_AR	SDL_SCANCODE_LEFT
# define RIGHT_AR	SDL_SCANCODE_RIGHT
# define UP_AR		SDL_SCANCODE_UP
# define DOWN_AR	SDL_SCANCODE_DOWN

# define LEFT	SDL_SCANCODE_A
# define RIGHT	SDL_SCANCODE_D
# define UP		SDL_SCANCODE_W
# define DOWN	SDL_SCANCODE_S

# define SPRINT	SDL_SCANCODE_LSHIFT


typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_dpos {
	double			x;
	double			y;
}					t_dpos;

typedef struct		s_pos {
	short			x;
	short			y;
}					t_pos;

typedef struct		s_vertex {
	int				id;
	int				x;
	int				y;
	struct s_vertex	*next;
	struct s_vertex	*prev;
}					t_vertex;

typedef struct		s_sdl {
	SDL_Window		*pwindow;
	SDL_Renderer	*prenderer;
	SDL_Event		event;
	t_texture		*map;
	t_texture		*game;
	t_texture		*editor;
	int				x_o;
	int				y_o;
	// t_sounds		sounds;
	Mix_Music		*musique;
}					t_sdl;

typedef struct		s_main {
	t_sdl			*sdl;
	t_dpos			p_pos;
	t_vertex		*vertex;
}					t_main;

//INITIALIZE

void				pre_initialize_sdl(t_main *s);
void				initialize_sdl(t_main *s, t_sdl *sdl);
t_texture			*initialize_texture(t_sdl *sdl, int width, int height);
t_main				*initialize_main(void);

void				display_error(int error_nb);
void				handle_error(t_main *s, int error_nb);
void				ft_error_sdl(char *str);

//IMAGES
void				update_image(t_main *s, t_texture *texture);
void				draw_rect(t_texture *text, t_dpos orig, t_dpos dest, Uint32 color);
void				set_pixel(t_texture *text, Uint32 color, t_pos coord);
void				draw_player(t_main *s, t_dpos p_pos);
void				ft_draw_grid(t_texture *tex);

//CONTROLS

int					keyboard_controls(t_main *s, int key);
void				event_handler(t_main *s);
void				handle_keys(t_main *s);

//MAP

int					ft_parcing(t_main *s);


#endif
