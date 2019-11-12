#ifndef EDITOR_H
# define EDITOR_H
# include "libft.h"
# include <SDL.h>
# include <SDL_mixer.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# define WIDTH 1000
# define HEIGHT 800
# define G_SPACE 30
# define METRE	30
# define GRID_SIDE_MARGIN 20
# define GRID_TOP_MARGIN 20
# define ROTATE_SPEED 20.00
# define PARSE_BUFF_SIZE 64

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LONG_MAX 9223372036854775807
# define DEF_TEX "images/textures/01.tga"

# define FILE_ERROR 1
# define SIZE_ERROR 2
# define SYNTAX_ERROR 3
# define MALLOC_ERROR 4
# define PLAYER_ERROR 5
# define WALL_ERROR 6
# define POINTER_ERROR 7
# define SECTOR_ERROR 8
# define MAP_ERROR 9

# define LEFT_AR		SDL_SCANCODE_LEFT
# define RIGHT_AR		SDL_SCANCODE_RIGHT
# define UP_AR			SDL_SCANCODE_UP
# define DOWN_AR		SDL_SCANCODE_DOWN

# define SPACE			32
# define LCTRL			SDL_SCANCODE_LCTRL
# define RCTRL			SDL_SCANCODE_RCTRL
# define SPRINT			SDL_SCANCODE_LSHIFT

# define LEFT			SDL_SCANCODE_A
# define RIGHT			SDL_SCANCODE_D
# define UP				SDL_SCANCODE_W
# define DOWN			SDL_SCANCODE_S
# define RIGHT_NUM		SDL_SCANCODE_1
# define LEFT_NUM		SDL_SCANCODE_2
# define MOVE			SDLK_v
# define WALL			SDLK_m
# define VERTEX			SDLK_b
# define PLAYER			SDLK_p
# define FLOOR			SDLK_f
# define SAVE			SDLK_u
# define SPRITE			SDLK_o
# define VISU			SDLK_i
# define PORTAL			SDLK_l
# define ROTATE_LEFT	SDLK_q
# define ROTATE_RIGHT	SDLK_e
# define HEALTH_PACK	SDLK_h
# define DAMAGE			SDLK_z
# define DEL 			8
# define TAB 			9
# define DELETE			SDLK_DELETE
# define MINUS			SDLK_MINUS

# define SPRINT	SDL_SCANCODE_LSHIFT

# define YELLOW 0xFFF73611
# define PINK 0xFF36F7FF
# define WHITE 0xFFFFFFFF
# define BLACK 0x000000FF
# define GREEN 0x32CD32FF
# define BLUE 0x57C7FFFF
# define BLACK_SCREEN 0x13131dFF
# define COLOR_WALL 0xff7062FF

# define S_YELLOW 0xFFF73611
# define S_PINK 0xFF36F7FF
# define S_BLUE 0x57C7FFFF
# define S_GREEN 0x32CD32FF
# define S_PURPLE 0xBA3FB8FF
# define S_BROWN 0xE19F3AFF
# define S_RED 0xCD15157F
# define S_ORANGE 0xED5F18FF
# define S_DBLUE 0x081EDBFF
# define S_DGREEN 0x288333FF

typedef enum			e_type {
	ennemi,
	boss,
	autre
}						t_type;

typedef enum			e_mode {
	move,
	sector,
	vertex,
	player,
	save_edi,
	portal,
	sprite
}						t_mode;

typedef struct			s_abpos {
	float				a;
	float				b;
}						t_abpos;

typedef struct			s_dpos {
	double				x;
	double				y;
}						t_dpos;

typedef struct			s_4double {
	double				d1;
	double				d2;
	double				d3;
	double				d4;
}						t_4double;

typedef struct			s_line {
	int					x1;
	int					x2;
	int					y1;
	int					y2;
	int					e;
	int					pixel_o;
	int					dx;
	int					dy;
}						t_line;

typedef struct			s_mouse {
	double				x;
	double				y;
}						t_mouse;

typedef struct			s_point {
	short				x;
	short				y;
	char				anchor;
	char				clicked;
}						t_point;

typedef struct			s_image {
	int					bits_color;
	int					bits_alpha;
	Uint32				*tex;
	int					w;
	int					h;
}						t_image;

typedef struct			s_anim {
	int					current;
	t_image				*image[15];
}						t_anim;

typedef struct			s_pos {
	short				x;
	short				y;
}						t_pos;

typedef struct			s_element {
	t_pos				pixel;
	struct s_element	*next;
}						t_element;

typedef struct			s_pile {
	t_element			*first;
}						t_pile;

typedef struct			s_vertex {
	int					id;
	int					x;
	int					y;
	t_pos				pos; // position en pixel en rapport a l'editeur
	t_pos				old;
	t_pos				save_pos;
	int					selec;
	char				selected;
	struct s_vertex		*next;
	struct s_vertex		*prev;
}						t_vertex;

typedef struct			s_int {
	int					id;
	int					value;
	t_vertex			*ptr;
	char				selected;
	int					sct;
	int					sct_dest;
	int					wall_value;
	t_image				*image;
	struct s_int		*vtx_dest;
	struct s_int		*next;
	struct s_int		*prev;
}						t_int;

typedef struct			s_sector {
	int					id;
	int					floor;
	int					ceiling;
	t_int				*vertex;
	struct s_sector		*next;
	struct s_sector		*prev;
}						t_sector;

typedef struct			s_editor {
	t_line				line;
	int					selected;
	int					space;
	int					anchor_size;
	int					decal_x;
	int					decal_y;
	t_pos				ref;
	t_mode				mode;
	char				color_sector;
	int					dply_floor;
	char				mode_floor;
	t_anim				menu;
	t_anim				m_floor;
	t_int				*wall;
	t_int				*wall2;
	char				portal_temp;
	int					over_portal;
	int					over_sector;
	int					over_sector2;
}						t_editor;

#endif
