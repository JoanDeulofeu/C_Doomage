#ifndef DOOM_H
# define DOOM_H

# include "editor.h"

# define SHIFT_AMOUNT 16
# define FOV 60
/// Fixed-point Format: 16.16 (32-bit)
typedef Uint32 fixed_float;

typedef struct		s_fix_pos {
	Uint32			x;
	Uint32			y;
}					t_fix_pos;

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_player
{
	t_dpos 			r_pos;
	t_dpos			pos;
	t_pos 			ori;
	t_pos 			p_ori;
	t_pos 			p_ref;
	t_line 			line;
	int 			set;
	int 			correc;
	int 			init_space;
	int 			angle;
	int				height;
}					t_player;

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
	t_editor		*editor;
	t_dpos			p_pos;
	t_mouse			ft_mouse;
	t_line			line;
	t_player		player;
	t_vertex		*vertex;
	t_sector		*sector;
	t_point			**grid;
	char			*str_vtx;
}					t_main;

/*
****	Fonction d'initialisation
*/
void				pre_initialize_sdl(t_main *s);
void				initialize_sdl(t_main *s, t_sdl *sdl);
t_texture			*initialize_texture(t_sdl *sdl, int width, int height);
t_main				*initialize_main(void);
void				free_program(t_main *s);

/*
****	Fonction de gestion d'erreur
*/
void				display_error(int error_nb);
void				handle_error(t_main *s, int error_nb);
void				ft_error_sdl(char *str);

/*
****	Fonction de l'editeur
*/
void				display_map(t_main *s);
void				get_grid_tab(t_main *s);
void				ft_draw_editor(t_editor *edi, t_texture *tex);
void				mouse_grid(t_main *s, t_pos save);

/*
****	Fonction de gestion d'images
*/
void				update_image(t_main *s, t_texture *texture);
void				draw_rect(t_texture *text, t_dpos orig, t_dpos dest, Uint32 color);
void				set_pixel(t_texture *text, Uint32 color, t_pos coord);
Uint32				get_pixel_color(t_texture *text, int x, int y);
void				draw_player(t_main *s, t_dpos p_pos);
void				draw_wall(t_main *s, t_pos ori);

/*
****	Fonction de creation de ligne
*/
int					trace_line(t_main *s, Uint32 color);
void				trace_vertical(t_main *s, Uint32 color);
void				get_line(t_main *s, Uint32 color);
void				ft_draw_all_wall(t_main *s);

/*
****	Fonction de gestion des controls
*/
int					keyboard_controls(t_main *s, int key);
void				editor_handler(t_main *s);
void				event_handler(t_main *s);
void				handle_keys(t_main *s);
void				change_mode(t_main *s, int key);
int					ft_prev_next_floor(t_main *s, char prev_next);
void				move_editor(t_main *s, const Uint8 *keys);


//MAP
int					ft_parsing(t_main *s, int x, int y, int fd);

/*
****	Fonction de gestion des listes chainés
*/
int					ft_add_vertex(t_main *s, int x, int y);
t_sector			*ft_add_sector(t_main *s, int floor, int ceiling);
int					ft_add_intarray(t_main *s, t_sector *array, int value, int what);
void				ft_test_chainlist(t_main *s);

/*
****	Fonction de gestion des vecteurs
*/
void				draw_anchor(t_main *s, t_pos ori, Uint32 color);
void				create_anchor(t_main *s, t_pos ori);
int					anchor_exists(t_main *s, t_pos ori);
void				set_selected(t_main *s, t_pos ori, char on);
t_pos				get_abs_pos(t_main *s, t_pos ori);
void				move_anchor(t_main *s, int id);
void				remove_anchor(t_main *s, int id);
void				remove_sector(t_main *s, int id, int del, int sct_id);
void				ft_reset_color_vertex(t_main *s);

/*
****	Fonction de gestion des secteurs
*/
int					ft_parse_sector(t_main *s, char *line);
int					ft_sector_mode(t_main *s, int x, int y);
void				fill_sectors(t_main *s);
void				draw_sector(t_main *s, int x, int y, Uint32 r_color);
t_int				*free_sector_struct(t_sector *temp_sector);

/*
****	Fonction utilitaire
*/
int					arround(int space, int nb);
t_pos 				get_px_pos(t_main *s, t_pos ref);
void				empiler(t_main *s, t_pile *pile, t_pos new_pixel);
t_pos				depiler(t_pile *pile);
int					ft_is_in_sector(t_main *s, t_pos point_2);
t_pos				ft_dpos_to_pos(t_dpos dpos);
t_dpos				ft_pos_to_dpos(t_pos pos);
void				ft_reset_color_screen(Uint32 *str, int size);
double  			to_rad(double angle);

/*
****	Fonction de gestion du joueur
*/
void 				set_player(t_main *s);
//void				ft_move_player(t_main *s, const Uint8 *key);
t_dpos				get_direction(t_main *s, const Uint8 *keys, double speed, t_dpos target);
void				ft_move_player(t_main *s, const Uint8 *keys, char sprint);
void 				rotate_player(t_main *s , const Uint8 *keys);
void				ft_trace_vertical(t_main *s, t_line line, Uint32 color);
void				ft_get_line(t_main *s, t_line line, Uint32 color);
int					ft_trace_line(t_main *s, t_line line, Uint32 color);
void 				trace_direction(t_main *s);

/*
****	Fonction des fixed float
*/
void				ft_test_float(void);
t_dpos				ft_fixfloat_to_dpos(t_fix_pos fix);
t_fix_pos			ft_dpos_to_fixfloat(t_dpos dpos);
fixed_float			ft_float_to_fixed(double input);
double				ft_fixed_to_float(fixed_float input);


#endif
