



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

# define INT_MAX 2147483647
# define INT_MIN -2147483648

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

# define LEFT	SDLK_a
# define RIGHT	SDLK_d
# define UP		SDLK_w
# define DOWN	SDLK_s
# define MOVE	SDLK_v
# define WALL	SDLK_m
# define VERTEX	SDLK_b
# define PLAYER	SDLK_p
# define FLOOR	SDLK_f
# define SUPP	SDLK_s
# define DELETE	SDLK_DELETE

# define SPRINT	SDL_SCANCODE_LSHIFT

# define YELLOW 0xFFF73611
# define PINK 0xFF36F7FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREEN 0x32CD32FF
# define BLUE 0x57C7FFFF
# define BLACK_SCREEN 0x13131dFF

typedef enum  	e_type {
	ennemi,
	boss,
	autre
}				t_type;

typedef enum  	e_mode {
	move,
	sector,
	vertex,
	player,
	m_floor,
	supp
}				t_mode;

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_abpos {
	float			a;
	float			b;
}					t_abpos;

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

typedef struct		s_element {
	t_pos			pixel;
	struct s_element *next;
}					t_element;

typedef struct		s_pile {
	t_element			*first;
}					t_pile;

typedef struct		s_sprite {
	int				id;
	t_pos			pos;
	t_type			type;
}					t_sprite;

typedef struct		s_player
{
	t_dpos 			r_pos;
	t_pos			pos;
	t_pos 			ori;
	t_pos 			p_ori;
	t_pos 			p_ref;
	int 			correc;
	int 			init_space;
}					t_player;

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
	t_pos			pos;
	char			selected;
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
	int				anchor_size;
	int				decal_x;
	int				decal_y;
	t_pos			ref;
	t_mode			mode;
	char			color_sector;
	int				dply_floor;
}					t_editor;

typedef struct		s_main {
	t_sdl			*sdl;
	t_editor		*editor;
	t_dpos			p_pos;
	t_mouse			ft_mouse;
	t_line			line;
	t_player		player;
	t_vertex		*vertex;
	t_sector		*sector;
	t_point			**grid;
	char			*str_vtx;	//save la liste des vertex du
								//secteur en cours de creation.

	// t_case			**map;
}					t_main;

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
void				mouse_grid(t_main *s, t_pos save);

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
void				ft_draw_all_wall(t_main *s);

//CONTROLS
int					keyboard_controls(t_main *s, int key);
void				editor_handler(t_main *s);
void				event_handler(t_main *s);
void				handle_keys(t_main *s);
void				change_mode(t_main *s, int key);
void				move_player(t_main *s, int key);
int					ft_prev_next_floor(t_main *s, char prev_next);


//MAP
int					ft_parsing(t_main *s, int x, int y, int fd);

//CHAINLIST
int					ft_add_vertex(t_main *s, int x, int y);
t_sector			*ft_add_sector(t_main *s, int floor, int ceiling);
int					ft_add_intarray(t_main *s, t_sector *array, int value, int what);
void				ft_test_chainlist(t_main *s);

//VERTEX
void				draw_anchor(t_main *s, t_pos ori, Uint32 color);
void				create_anchor(t_main *s, t_pos ori);
int					anchor_exists(t_main *s, t_pos ori);
void				set_selected(t_main *s, t_pos ori, char on);

t_pos				get_abs_pos(t_main *s, t_pos ori);
void				move_anchor(t_main *s, int id);
void				remove_anchor(t_main *s, int id);
void				remove_sector(t_main *s, int id, int del, int sct_id);
void				ft_reset_color_vertex(t_main *s);

//SECTOR
int					ft_parse_sector(t_main *s, char *line);
int					ft_sector_mode(t_main *s, int x, int y);
void				draw_sector(t_main *s, int x, int y, Uint32 r_color);

//UTILS
int					arround(int space, int nb);
Uint32				get_pixel_color(t_texture *text, int x, int y);
t_pos 				get_px_pos(t_main *s, t_pos ref);
void				empiler(t_main *s, t_pile *pile, t_pos new_pixel);
t_pos				depiler(t_pile *pile);
int					ft_is_in_sector(t_main *s, t_pos point_2);
t_pos				ft_dpos_to_pos(t_dpos dpos);
t_dpos				ft_pos_to_dpos(t_pos pos);
void				ft_reset_color_screen(Uint32 *str, int size);
#endif
