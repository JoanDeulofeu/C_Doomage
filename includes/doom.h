#ifndef DOOM_H
# define DOOM_H

# include "editor.h"
# include <SDL_ttf.h>

# define SHIFT_AMOUNT 8
# define VFOV .2f * HEIGHT
# define HFOV 0.73f * HEIGHT
# define FOV 60
# define MAX_QUEUE 32

# define WALL_HEIGHT 10
// # define METRE 30
# define DIVPLAN 20
# define WIDTHPLAN (WIDTH / DIVPLAN)
# define EYESIGHT 10
# define MAX_SPRITE_DIST 1500

# define HITBOX 2
# define SPRITE_HITBOX 10

# define PORTAL_LIMIT 20

# define MAP "map.map"

//sprite
#define ANGLE_MAX 360
#define SPRITE_DETECTION 5
#define SPRITE_SHOT_DIST 3
#define SPRITE_MOVE_SPEED 0.1

/// Fixed-point Format: 16.16 (32-bit)
typedef int32_t fixed_float;

typedef enum  				e_display_mode {
	editor,
	game,
	save,
}							t_display_mode;

typedef struct				s_fix_pos {
	Uint32					x;
	Uint32					y;
}							t_fix_pos;

typedef struct				s_ttf {
	SDL_Rect				pos;
	char					*str;
	int						r;
	int						g;
	int						b;
}							t_ttf;

typedef struct				s_texture {
	Uint32					*content;
	SDL_Texture				*texture;
	Uint32					color_tmp;
}							t_texture;

typedef struct				s_visu_sct
{
	int						sector_id;
	int						sx1;
	int						sx2;
}							t_visu_sct;

typedef struct				s_time
{
	int						action;
	t_pos 					recoil;
	long					fin_time;
	long					tmp_time;
	char					v0id[32];
}							t_time;

typedef struct				s_lanim
{
	int						id;
	int						max_current;
	t_image					*image[15];
}							t_lanim;


typedef struct				s_lsprite
{
	int						id;
	t_image 				*img;
	t_lanim 				*anim;
	struct s_lsprite		*next;
}							t_lsprite;

typedef struct				s_sprite
{
	int						id;
	int						set;
	int						orientation;
	int						select;
	int						life;
	int						current;
	int						destroy;
	double 					angle;
	double 					s_angle;
	double 					dist;
	double 					r_dist;
	t_dpos					r_pos;
	t_pos					pos;
	t_type					type;
	t_image 				*img;
	t_lanim 				*anim;
	struct s_sprite			*next;
}							t_sprite;


typedef struct				s_player
{
	long					j_fin_time;
	long					fin_time;
	long					tmp_time;
	int 					set_jump;
	int 					i;
	t_dpos 					r_pos; // position reel du joueur par rpport au repere
	t_dpos					pos; // Position du joueur en pixel
	t_pos 					ori; //position du joueur en case (avant correction)
	t_pos 					p_ori; //valeur en pixel à rajouter pour avoir la position
	t_pos 					p_ref; // decalage en pixel par rapport a la ref
	t_line 					line;
	int 					set;
	int 					correc;
	int 					init_space;
	int						sector_id;
	int 					eyesight;
	int 					y_eye;
	double					angle;
	int						height;
	t_anim					weapon;
	t_time 					t;
	t_image					*hud;
	t_image					*crosshair;
	t_sector				*sector;
}							t_player;

typedef struct				s_visu {
	t_dpos					tmp_wall;
	t_dpos					left_plan;
	t_dpos					right_plan;
	t_dpos					begin;
	int						begin_wall_id;
	t_int					*begin_wall;
	t_dpos					end;
	int						end_wall_id;
	t_pos					pixel;
	Uint32					color;
	t_dpos					left_point;
	t_dpos					right_point;
	t_dpos					player;
	double					angle;
	int						sct_id;
	t_sector				*sct;
	t_int					*vtx_gauche;
	t_int					*vtx_droite;
}							t_visu;

typedef struct				s_walls {
	double					distance;
	int						x;
	t_dpos					player;
	t_dpos					left;
	t_dpos					right;
	t_dpos					l_plan;
	t_dpos					r_plan;
	struct s_walls			*prev;
	struct s_walls			*next;
}							t_walls;

typedef struct				s_savemap {
	t_image					*croix_rouge;
	char					str[41];
	short					error_msg;
}							t_savemap;

typedef struct				s_sdl {
	SDL_Window				*pwindow;
	SDL_Renderer			*prenderer;
	SDL_Event				event;
	t_texture				*map;
	t_texture				*game;
	t_texture				*editor;
	t_texture				*save; //ecran de sauvegarde
	int						x_o;
	int						y_o;
	// t_sounds				sounds;
	Mix_Music				*musique;
}							t_sdl;

typedef struct				s_font {
	TTF_Font				*press_start;
	TTF_Font				*open;
	TTF_Font				*roboto;
	TTF_Font				*stylish;
	TTF_Font				*stylish100;
}							t_font;

typedef struct				s_main {
	t_font					*font;
	t_sdl					*sdl;
	t_editor				*editor;
	t_savemap				*savemap;
	char					*map_name;
	t_dpos					p_pos;
	t_dpos					left_plan;
	t_dpos					right_plan;
	t_pos					ft_mouse;
	t_line					line;
	t_visu					visu;
	t_player				player;
	t_dpos					tmp_intersect;
	t_dpos					intersect1;
	t_dpos					intersect2;
	t_vertex				*vertex;
	t_sector				*sector;
	t_point					**grid;
	char		 			*str_vtx;
	t_display_mode			display_mode;
	int						viewline;
	int						proj_distance;
	t_image					*menu;
	t_image					*interface;
	t_image					*skybox;
	short					fov;
	t_sprite				*sprite;
	t_lsprite				*lsprite;
	t_lsprite				*choice_sprite;
	t_walls					*walls;
	int						portal_nb;
	t_dpos					col_pos;
	t_dpos					fplayer_pos;
	double					fplayer_angle;
	int						fplayer_sct;
}							t_main;

/*
****	Fonction du visualisateur
*/
void				ft_visu(t_main *s);
void				ft_visu_joan(t_main *s, const unsigned char *keys);
void 				ft_draw_visu(t_main *s, t_dpos player, t_sector *sct, t_visu vs);
int					check_walls_lenght(t_int *wall1, t_int *wall2);
t_visu				ft_place_view_plan(t_main *s, t_dpos player, double angle, Uint32 color);
void 				ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs);
void				draw_first_wall(t_main *s, t_int *vtx, t_visu *vs);
t_int				*draw_mid_walls(t_main *s, t_int *vtx, t_visu *vs);
void				draw_last_wall(t_main *s, t_int *vtx, t_visu *vs);
int					ft_find_wall2(t_main *s, t_dpos player, t_dpos point, Uint32 color, int sct_id);
int					ft_print_wall(t_main *s, int x, t_dpos player, t_dpos lwall, t_dpos rwall, t_dpos lplan, t_dpos rplan);

/*
****	Fonction d'initialisation
*/
void				pre_initialize_sdl(t_main *s);
void				initialize_sdl(t_main *s, t_sdl *sdl);
t_texture			*initialize_texture(t_sdl *sdl, int width, int height);
t_main				*initialize_main(char *str);
void				free_program(t_main *s);

/*
****	Fonction de gestion d'erreur
*/
void				display_error(int error_nb);
void				handle_error(t_main *s, int error_nb);
void				ft_error_sdl(char *str);
void				ft_error_ttf(char *str);

/*
****	Fonction du menu principal
*/
int					handle_menu(t_main *s);
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
int					trace_line(t_main *s, Uint32 color, int w);
void				trace_vertical(t_main *s, Uint32 color, int w);
void				get_line(t_main *s, Uint32 color, int w);
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
int					ft_find_next_number(char *str, int i);
void				ft_check_validity_last_sector(t_main *s);

/*
****	Fonction de gestion des listes chainés
*/
int					ft_add_vertex(t_main *s, int x, int y);
int					ft_check_vertex(t_main *s, int x, int y);
t_sector			*ft_add_sector(t_main *s, int floor, int ceiling);
int					ft_add_intarray(t_main *s, t_sector *array, int value);
void				put_wall_value(t_sector *sector, char *line, int i);
void				ft_test_chainlist(t_main *s);
t_int				*get_t_int_by_vertex_id(t_int *vtx, int ptr_id);

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
int					get_nearest_sector(t_main *s, t_pos pos, t_pos *new_pos);
t_dpos				handle_sector_zero(t_main *s, const unsigned char *keys);

/*
****	Fonction de gestion des portails
*/
void				change_over_wall(t_main *s);
void				edit_portal(t_main *s);
void				remove_portal(t_main *s);
void				reset_temp_portals(t_main *s);
t_dpos				ft_get_fake_player(t_main *s, t_dpos player, t_int *vtx, double *angle_portal_out);
t_visu				get_walls_to_draw(t_main *s, t_dpos player, double l_angle, double r_angle, t_visu vs);
void				add_portal_to_list(t_main *s, t_dpos player, t_sector *sct, t_visu vs);

/*
****	Fonction utilitaire
*/
int					arround(int space, int nb);
t_pos 				get_px_pos(t_main *s, t_pos ref);
void				empiler(t_main *s, t_pile *pile, t_pos new_pixel);
t_pos				depiler(t_pile *pile);
int					ft_is_in_sector(t_main *s, t_pos point_2);
int					ft_find_intersection(t_main *s, t_dpos begin_l1, t_dpos end_l1, t_dpos begin_l2, t_dpos end_l2, char visu);
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
double				ft_find_angle_plan(double a, double b, double c);
double				vxs(double x1, double y1, double x2, double y2);
int					ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end);

void				ft_trace_vertical_select(t_main *s, t_line line, Uint32 color);
int					ft_trace_line_select(t_main *s, t_line line, Uint32 color);
void				ft_get_line_select(t_main *s, t_line line, Uint32 color);
void 				trace_select(t_main *s);
void				remove_selected_anchor(t_main *s);



/*
****	Fonction de gestion du joueur
*/
void 				set_player(t_main *s);
//void				ft_move_player(t_main *s, const Uint8 *key);
t_dpos				get_direction(t_main *s, const Uint8 *keys, double speed, t_dpos target);
void				ft_move_player(t_main *s, const Uint8 *keys, int move_speed);
void 				rotate_player(t_main *s , const Uint8 *keys);
void 				teleport_player(t_main *s, const unsigned char *keys);
void				ft_trace_vertical(t_main *s, t_line line, Uint32 color);
void				ft_get_line(t_main *s, t_line line, Uint32 color);
int					ft_trace_line(t_main *s, t_line line, Uint32 color);
void 				trace_direction(t_main *s);
void  				rotate_mouse(t_main *s);
void 				jump(t_main *s, int press);
void 				crouch(t_main *s, int press);
void				draw_weapon(t_main *s, double perx, short orig_x, short orig_y);
void 				draw_hud(t_main *s);
void				display_hud(t_main *s, int i, int j);
void 				shoot(t_main *s, int press);
void 				display_crosshair(t_main *s, int i, int j);
void 				draw_weapon2(t_main *s, int i, int j);
int					is_colliding(t_main *s);

/*
****	Fonction de sauvegarde
*/
void				ft_save_map(t_main *s);
void				ft_click_save(t_main *s);
void				ft_add_letter_to_savemap(t_main *s, int key);
void				ft_del_letter_to_savemap(t_main *s);
void				ft_save_msg(t_main *s, int error);
void				ft_write_file(t_main *s);


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

/*
****	Fonction des ttf
*/
void				ft_create_ttf(t_ttf ttf, t_main *s, TTF_Font *police);
void				ft_init_font(t_main *s);
void				ft_draw_ttf(t_main *s);

/*
****	Fonction de debug
*/
void 				print_wall_list(t_main *s);

/*
****	Fonction des textures
*/
void				draw_skybox(t_main *s, t_visu vs);

/*FCT SPRITE CHAINLIST*/
t_pos 	get_px_r_pos(t_main *s, t_dpos ref);
void	*ft_memalloc(size_t size);
t_lsprite 				*load_lsprite(t_main *s,t_lsprite *start, int size);

t_lsprite 		*create_lsprite_elem(t_main *s, int id);
t_lsprite 		*create_lsprite(t_main *s, int size);
t_sprite 		*create_sprite_elem(t_main *s, int id, int idimg, t_dpos pos);
void	add_sprite(t_main *s, t_dpos pos, int idimg);
void             init_sprite(t_main *s);
void        refresh_sprite_pos(t_main *s);
double      calc_sprite_dist(t_main *s, t_pos pos);
double      calc_sprite_r_dist(t_main *s, t_dpos pos);
int 	check_is_on_sector(t_main *s, t_sprite *cur);



void 	display_by_id(t_main *s, int id);
int 	found_farther(t_main *s);
int 	found_closer(t_main *s);

void  found_sprite(t_main *s);

void 				draw_sprite(t_main *s);
void display_sprite(t_main *s,double angle, t_sprite *cur);
int 	check_sprite_menu_click(t_main *s, t_pos pos);
void draw_sprite_menu(t_main *s);
void display_sprite_inverse(t_main *s,double angle, t_sprite *cur);







void 	free_sprite(t_main *s);
void 	free_lsprite(t_main *s);
void 	free_anim(t_lanim *anim);

void 				remove_sprite_by_id(t_main *s, int id);
void 				remove_sprite_by_select(t_main *s);
void 				remove_sprite(t_main *s, t_sprite *cur, t_sprite *next,t_sprite *prev);



t_dpos	get_abs_r_pos(t_main *s, t_pos ori);

//mode selection

void select_vertex(t_main *s);
void 	deselect_vertex(t_main *s);
void move_vertex(t_main *s, t_pos tmp_move, t_pos ori, int id);
int exist_vertex(t_main *s, t_pos *mouse_save, int *id, t_pos *ori);
void 				reset_id(t_main *s);
int 				found_id_sprite(t_main *s, t_pos start, t_pos end);

void 	deselect_sprite(t_main *s);
void select_sprite(t_main *s);
int set_selected_sprite(t_main *s, t_pos *mouse_save);


void 	display_chainlist(t_main *s);


int   check_exist(t_main *s,t_dpos target, int id);
void	fire(t_main *s);
// void    sprite_move(t_main *s);
void    sprite_move_on_player(t_main *s,t_sprite *cur);
void  ia(t_main*s,t_sprite *cur);


void  rand_move(t_main *s,t_sprite *cur);





//load anim
void 				load_anim1(t_lanim *data);
void 				load_anim2(t_lanim *data);
void 				load_anim3(t_lanim *data);
void 				load_anim4(t_lanim *data);
void 				load_anim5(t_lanim *data);
void 				load_anim6(t_lanim *data);
void 				load_anim7(t_lanim *data);

//animation
void 				kill(t_sprite *cur);

void        play_anim(t_main *s);

void   sprite_shooting(t_main *s,t_sprite *cur);
void  sprite_walk(t_sprite *cur);
void  dying(t_main *s,t_sprite *cur);
void 			set_img(t_main *s,t_sprite *cur, int id, int orientation);
void 			set_orientation(t_main *s, t_sprite *cur);

t_lanim        *get_anim_by_id(t_main *s, int id);









#endif
