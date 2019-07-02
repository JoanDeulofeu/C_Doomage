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
# define G_SPACE 30
# define GRID_SIDE_MARGIN 20
# define GRID_TOP_MARGIN 20

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

# define WHITE 0xFFFFFFFF
# define GREEN 0x32CD32FF
# define BLUE 0x0000FFFF

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_dpos {
	double			x;
	double			y;
}					t_dpos;

typedef struct		s_line {
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				e;
	int				pixel_o;
	int				dx;
	int				dy;
}					t_line;

typedef struct		s_mouse {
	double			x;
	double			y;
}					t_mouse;

typedef struct		s_point {
	short			x;
	short			y;
	char			anchor;
	char			clicked;
}					t_point;

typedef struct		s_pos {
	short			x;
	short			y;
}					t_pos;

typedef struct		s_int {
	int				id;
	int				value;
	struct s_int	*next;
	struct s_int	*prev;
}					t_int;

typedef struct		s_vertex {
	int				id;
	int				x;
	int				y;
	struct s_vertex	*next;
	struct s_vertex	*prev;
}					t_vertex;

typedef struct		s_sector {
	int				id;
	int				floor;
	int				ceiling;
	t_int			*vertex;
	t_int			*wall;
	struct s_sector	*next;
	struct s_sector	*prev;
}					t_sector;

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

typedef struct		s_editor {
	int				space;
	int				decal_x;
	int				decal_y;
	t_pos			ref;
}					t_editor;

typedef struct		s_main {
	t_sdl			*sdl;
	t_editor		*editor;
	t_dpos			p_pos;
	t_mouse			ft_mouse;
	t_line			line;
	t_vertex		*vertex;
	t_sector		*sector;
	t_point			**grid;


	// t_case			**map;
}					t_main;

typedef enum  s_mode {
	move, wall, vertex;
};

//INITIALIZE

void				pre_initialize_sdl(t_main *s);
void				initialize_sdl(t_main *s, t_sdl *sdl);
t_texture			*initialize_texture(t_sdl *sdl, int width, int height);
t_main				*initialize_main(void);

void				display_error(int error_nb);
void				handle_error(t_main *s, int error_nb);
void				ft_error_sdl(char *str);

//EDITOR

void				display_map(t_main *s);
void				get_grid_tab(t_main *s);
void				ft_draw_editor(t_editor *edi, t_texture *tex);

//IMAGES
void				update_image(t_main *s, t_texture *texture);
void				draw_rect(t_texture *text, t_dpos orig, t_dpos dest, Uint32 color);
void				set_pixel(t_texture *text, Uint32 color, t_pos coord);
void				draw_player(t_main *s, t_dpos p_pos);
void				draw_wall(t_main *s, t_pos ori);

//LINES

int					trace_line(t_main *s, Uint32 color);
void				trace_vertical(t_main *s, Uint32 color);
void				get_line(t_main *s, Uint32 color);

//CONTROLS

int					keyboard_controls(t_main *s, int key);
void				editor_handler(t_main *s);
void				event_handler(t_main *s);
void				handle_keys(t_main *s);

//MAP

int					ft_parsing(t_main *s);

//CHAINLIST

int					ft_add_vertex(t_main *s, int x, int y);
t_sector			*ft_add_sector(t_main *s, int floor, int ceiling);
int					ft_add_intarray(t_main *s, t_sector *array, int value, int what);
void				ft_test_chainlist(t_main *s);

//UTILS

int					arround(int space, int nb);

#endif
