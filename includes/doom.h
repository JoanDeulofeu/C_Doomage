#ifndef DOOM_H
# define DOOM_H

# include "editor.h"

# define SHIFT_AMOUNT 8
# define VFOV .2f * HEIGHT
# define HFOV 0.73f * HEIGHT
# define FOV 60
# define MAX_QUEUE 30

# define WALL_HEIGHT 10
// # define METRE 30
# define DIVPLAN 20
# define WIDTHPLAN (WIDTH / DIVPLAN)
# define EYESIGHT 10

/// Fixed-point Format: 16.16 (32-bit)
typedef int32_t fixed_float;

typedef struct		s_fix_pos {
	Uint32			x;
	Uint32			y;
}					t_fix_pos;

typedef struct		s_texture {
	Uint32			*content;
	SDL_Texture		*texture;
	Uint32			color_tmp;
}					t_texture;

typedef struct		s_visu_sct
{
	int				sector_id;
	int				sx1;
	int				sx2;
}					t_visu_sct;

typedef struct		s_player
{
	long			fin_time;
	long			tmp_time;
	int 			i;
	t_dpos 			r_pos; // position reel du joueur par rpport au repere
	t_dpos			pos; // Position du joueur en pixel
	t_pos 			ori; //position du joueur en case (avant correction)
	t_pos 			p_ori; //valeur en pixel à rajouter pour avoir la position
	t_pos 			p_ref; // decalage en pixel par rapport a la ref
	t_line 			line;
	int 			set;
	int 			correc;
	int 			init_space;
	int				sector_id;
	int 			eyesight;
	double			angle;
	int				height;
	t_sector		*sector;
}					t_player;

typedef struct		s_visu {
	t_dpos			tmp_wall;
	t_dpos			left_plan;
	t_dpos			right_plan;
	t_dpos			begin;
	int				begin_wall;
	t_dpos			end;
	int				end_wall;
}					t_visu;

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
	t_dpos			left_plan;
	t_dpos			right_plan;
	t_pos			ft_mouse;
	t_line			line;
	t_visu			visu;
	t_player		player;
	t_dpos			tmp_intersect;
	t_dpos			intersect1;
	t_dpos			intersect2;
	t_vertex		*vertex;
	t_sector		*sector;
	t_point			**grid;
	char			*str_vtx;
	char			player_view;
}					t_main;

/*
****	Fonction du visualisateur
*/
void				ft_visu(t_main *s);
void				ft_visu_joan(t_main *s);
void				ft_draw_visu(t_main *s, t_dpos player, t_visu *vs);

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
t_image				*load_tga(char *path, int i, int idx, int ret);
void				draw_image(t_texture *texture, t_pos ori, t_pos dest, t_image *image);
void				draw_space_menu(t_main *s);
void				draw_editor_menu(t_main *s, double perx, short orig_x, short orig_y);

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
int					ft_check_vertex(t_main *s, int x, int y);
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
int					ft_find_intersection(t_main *s, t_dpos begin_l1, t_dpos end_l1, t_dpos begin_l2, t_dpos end_l2);
t_pos				ft_dpos_to_pos(t_dpos dpos);
t_dpos				ft_pos_to_dpos(t_pos pos);
void				ft_reset_color_screen(Uint32 *str, int size);
double  			to_rad(double angle);
double				to_degres(double rad);
double				percent(double value, double total);
t_sector			*get_sector_by_id(t_main *s, int id);
t_vertex			*get_vertex_by_id(t_main *s, int id);
t_int				*get_t_int_by_id(t_int *obj, int id);
double				ft_dist_double(double x1, double y1, double x2, double y2);
double				ft_dist_t_dpos(t_dpos pos1, t_dpos pos2);
int					clamp (int x, int min, int max);
void  				ft_zoom(t_main *s, t_pos pos, int space);
int					max(int value1, int value2);
int					min(int value1, int value2);


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
void  				rotate_mouse(t_main *s, t_pos mouse, t_pos mouse_save);
void 				jump(t_main *s);
void 				crouch(t_main *s, int press);




/*
****	Fonction des fixed float
*/
void				ft_test_float(void);
t_dpos				ft_fixfloat_to_dpos(t_fix_pos fix);
t_fix_pos			ft_dpos_to_fixfloat(t_dpos dpos);
fixed_float			ft_float_to_fixed(double input);
double				ft_fixed_to_float(fixed_float input);
fixed_float			ft_fixed_pow(fixed_float nb, int power);
fixed_float			ft_fixed_sqrt(fixed_float nb);
fixed_float			ft_fixed_mul(fixed_float a, fixed_float b);


#endif
