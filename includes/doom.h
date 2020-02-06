#ifndef DOOM_H
# define DOOM_H

# include "editor.h"
# include <SDL_ttf.h>

# define SHIFT_AMOUNT 8
# define VFOV .2f * HEIGHT
# define HFOV 0.73f * HEIGHT
# define FOV 60
# define MAX_QUEUE 32
# define MAX_TEXTURES 11

# define WALL_HEIGHT 10
# define HEIGHT_MULT 0.5
# define DIVPLAN 20
# define WIDTHPLAN (WIDTH / DIVPLAN)
# define EYESIGHT 0
# define MAX_SPRITE_DIST 1500

# define HITBOX 2
# define SPRITE_HITBOX 10

# define TRANSITION_SPEED 30
# define MOON_X 60
# define MOON_Y 520

# define PORTAL_LIMIT 20
# define PLAYER_SIZE 2
# define PLAYER_SPEED 4
# define JUMP_SIZE 1.1

# define W_MUL 2.6

# define MAP "map.map"

//sprite
# define ANGLE_MAX 360
# define SPRITE_DETECTION 5
# define SPRITE_SHOT_DIST 3
# define SPRITE_MOVE_SPEED 0.1
# define STORM_RANGE 6
# define JET_TIME 10000

// Fixed-point Format: 16.16 (32-bit)
typedef int32_t				fixed_float;

typedef enum				e_display_mode {
	editor,
	game,
	save,
}							t_display_mode;

typedef enum				e_wp_name {
	kick,
	gun,
	shotgun
}							t_wp_name;

typedef struct				s_fix_pos {
	Uint32					x;
	Uint32					y;
}							t_fix_pos;

typedef struct				s_4dpos {
	t_dpos					pos1;
	t_dpos					pos2;
	t_dpos					pos3;
	t_dpos					pos4;
}							t_4dpos;

typedef	struct				s_sounds
{
	// Mix_Chunk				*shot;
	Mix_Chunk				*select;
	Mix_Chunk				*explode;
	Mix_Chunk				*shotgun;
	Mix_Chunk				*gun;
	Mix_Chunk				*blaster;
}							t_sounds;

typedef struct				s_ft_find_wall {
	t_sector				*sct;
	t_int					*s_vtx;
	t_4dpos					pos;
	int						id_wall;
	int						i;
	int						dist;
	int						new_dist;
}							t_ft_find_wall;

typedef struct				s_check_pos_sector {
	t_int					*wall;
	int						count;
	long					save_dist;
	long					tmp_dist;
	int						n_test;
	int						dist_sector;
	int						i;
}							t_check_pos_sector;

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

typedef struct				s_player
{
	int						dead;
	int						i; //???
	double					demi_fov;
	t_dpos					r_ori;
	t_dpos					r_pos; // position reel du joueur par rpport au repere
	t_dpos					pos; // Position du joueur en pixel
	t_dpos					m_pos;// positon reel * METRE
	t_line					line;
	double					size;
	double					foot_height;
	char					jump; //0 = pas de jump, 1 = phase montante, 2 = descendante
	double					jump_height;
	double					prev_jump_height;
	char					fly; //0 = pas de fly, 1 = fly
	double					tumble;
	int						set;
	int						shoot;
	int						correc;
	int						init_space;
	int						sector_id;
	double					eyesight;
	int						y_eye;
	int						health;
	int						armor;
	int						keys;
	int						mun_gun;
	int						mun_shotgun;
	double					angle;
	double					abs_angle;
	int						floor_height;
	int						ceiling_height;
	int						jetpack;
	t_anim					weapon;
	int						range;
	int						power;
	t_wp_name				wp_name;
	int						wp_wheel[3]; //roue des armes
	t_image					*hud;
	t_image					*crosshair;
	t_sector				*sector;
}							t_player;

typedef struct				s_skybox {
	t_dpos					player;
	t_dpos					left_point;
	t_dpos					right_point;
}							t_skybox;

typedef struct				s_visu {
	t_dpos					tmp_wall;
	t_dpos					left_plan;
	t_dpos					right_plan;
	t_dpos					begin;
	int						begin_wall_id;
	t_int					*begin_wall;
	t_dpos					end;
	int						end_wall_id;
	Uint32					color;
	t_dpos					left_point;
	t_dpos					right_point;
	t_dpos					player;
	double					angle;
	int						prev_sct_id; //sct_id du sct AVANT de passer le portail
	int						sct_id; //sct_id du sct APRES de passer le portail
	t_sector				*sct;
	t_int					*vtx_gauche;
	t_int					*vtx_droite;
	t_pos					right_ceiling_limit;
	t_pos					left_ceiling_limit;
	t_pos					right_floor_limit;
	t_pos					left_floor_limit;
}							t_visu;

typedef struct				s_walls {
	int						id;
	int						occuped;
	char					wall_or_portal; //wall = "w", portal = "p";
	int						portal_value;
	int						sct_id;
	double					l_dist;
	double					b_dist;
	int						x;
	double					angle; //angle du fake_player
	t_dpos					player;
	int						screen_width_wall;
	long 					total_width_wall;
	int						left_void_side; //cote gauche entre total et screen
	int						avcm_x;
	t_dpos					left;
	t_dpos					right;
	t_dpos					r_left; //ptr gauche du mur
	t_dpos					r_right; //ptr droite du mur
	t_dpos					l_plan;
	t_dpos					r_plan;
	t_pos					right_ceiling_limit;
	t_pos					left_ceiling_limit;
	t_pos					right_floor_limit;
	t_pos					left_floor_limit;
	int						diffx_ceiling;
	int						diffy_ceiling;
	int						diffx_floor;
	int						diffy_floor;
	int						minx_ceiling;
	int						miny_ceiling;
	int						minx_floor;
	int						miny_floor;
	int						floor_height;
	int						ceiling_height;
	int						floor_height_dest; // dans le cas dun sct
	int						ceiling_height_dest; // dans le cas dun sct
	int						wall_height_tmp;
	int						nb_tex;
	t_image					*image;
	struct s_walls			*prev;
	struct s_walls			*next;
}							t_walls;

typedef struct				s_savemap {
	t_image					*croix_rouge;
	char					str[41];
	short					error_msg;
}							t_savemap;

typedef struct				s_ennemi {
	int						damage;

}							t_ennemi;

typedef struct				s_sdl {
	SDL_Window				*pwindow;
	SDL_Renderer			*prenderer;
	SDL_Event				event;
	t_texture				*map;
	t_texture				*game;
	t_texture				*editor;
	t_texture				*save;
	int						x_o;
	int						y_o;
	t_sounds				sounds;
	Mix_Music				*musique;
}							t_sdl;

typedef struct				s_font {
	TTF_Font				*press_start;
	TTF_Font				*press_start25;
	TTF_Font				*open;
	TTF_Font				*roboto;
	TTF_Font				*stylish;
	TTF_Font				*stylish100;
	TTF_Font				*digit;
	TTF_Font				*digit42;
}							t_font;

typedef struct				s_timer {
	long					time_ms;
	int						count_fps;
	int						tmp_sec_fps;
	int						fps;
	long					msg_tmp_ms;
	long					crouch_ms;
	long					jump_ms;
	long					shotgun_ms;
	long					g_o_ms;
	long					explosion_ms;
	long					jetpack_ms;
	long					jetpack_reserve;
}							t_timer;

typedef struct				s_msg {
	int						r;
	int						g;
	int						b;
	int						duration;
	char					*message;
}							t_msg;

typedef struct				s_main {
	pthread_t				thread[4];
	int						block_move;
	int						transition;
	int						transition_y_eye;
	int						transition_angle;
	int						sct_without_ceiling;
	int						printf;
	int						count_wall;
	int						wall_fk_id;
	int						play_or_editor;
	t_timer					*time;
	t_msg					*msg;
	t_font					*font;
	t_sdl					*sdl;
	t_editor				*editor;
	t_savemap				*savemap;
	char					*map_name;
	t_anim_enemy			stormtrooper;
	t_anim_wp				wp_anims;
	t_dpos					p_pos;
	t_dpos					left_plan;
	t_dpos					right_plan;
	t_pos					ft_mouse;
	t_line					line;
	t_visu					visu;
	t_player				player;
	t_ennemi				ennemi;
	t_dpos					tmp_intersect;
	t_dpos					intersect1;
	t_dpos					intersect2;
	t_vertex				*vertex;
	t_sector				*sector;
	char					*str_vtx;
	t_display_mode			display_mode;
	int						viewline;
	int						proj_distance;
	t_anim					menu;
	t_anim					gameover;
	t_image					*interface;
	t_anim					skybox;
	t_anim					cinematic;
	short					fov;
	t_sprite				*sprite;
	t_static				items;
	t_walls					*walls;
	int						portal_nb;
	t_dpos					col_pos;
	t_pos					save_coord_vtx;
}							t_main;

typedef struct				s_multithread {
	t_main					*s;
	t_walls					*wall;
	double					l_height_wall;
	double					r_height_wall;
	int						width_wall;
	int						wall_height_tmp;
	int						avcm_x;
}							t_multithread;

void 						reset(t_main *s);
void 						ending(t_main *s, int key);
void						reset_statue(t_main *s);
/*
****	Fonction du multithreading
*/
void						ft_multi_threading(t_main *s, t_walls *wall, double l_height_wall, double r_height_wall, int width_wall);

/*
****	Fonction du visualisateur
*/
void						ft_visu(t_main *s);
t_visu						move_player_near_portal(t_main *s, t_visu vs, int nb);
void						ft_visu_joan(t_main *s);
void 						ft_draw_visu(t_main *s, t_sector *sct, t_visu vs);
int							check_walls_lenght(t_int *wall1, t_int *wall2);
t_visu						ft_place_view_plan(t_dpos player, double angle);
t_walls 					*ft_create_new_wall(t_main *s, t_int *vtx, t_visu *vs, char w_or_p);
void						create_all_walls(t_main *s, t_int *vtx, t_visu *vs, int end);
int							ft_find_wall(t_main *s, t_dpos player, t_dpos point, int sct_id);
void						ft_print_wall(t_main *s, t_walls *wall);
void						add_wall_to_list(t_main *s, t_walls *new);
void						clear_wall_list(t_main *s);
void						ft_limit_ceiling_floor(t_main *s,t_dpos left,
							t_dpos right, t_visu *vs, char swich);
double						ft_find_angle_portal(t_dpos *left, t_dpos *right,
							t_dpos *third, int needed);
void						get_wall_distance(t_walls *wall, t_visu *vs);
int							ft_draw_wall(t_main *s, t_walls *wall, double l_height_wall,
	 						double r_height_wall, int width_wall);
int							ft_get_diff_height_pxl(double eyesight, int ceiling_height,
							int floor_height, int height_wall);
int							ft_get_sprite_height_pxl(t_main *s, t_sprite *sprite, double height);

/*
****	Fonction d'initialisation
*/
void						pre_initialize_sdl(t_main *s);
void						initialize_sdl(t_main *s, t_sdl *sdl);
t_texture					*initialize_texture(t_sdl *sdl, int width, int height);
t_anim_wp 					load_wp_anims(t_main *s);
void						fill_sprite_list(t_main *s);
t_main						*initialize_main(char *str);
void						free_program(t_main *s);
void						free_images_1(t_main *s);
void						free_image(t_image *img);
void						free_anim(t_anim anim);
void						free_sprite(t_main *s);

/*
****	Fonction de gestion d'erreur
*/
void						display_error(int error_nb);
void						handle_error(t_main *s, int error_nb);
void						ft_error_sdl(char *str);
void						ft_error_ttf(char *str);

/*
****	Fonction du menu principal
*/
int							handle_menu(t_main *s);
void 						launch_game(t_main *s);
void 						launch_editor(t_main *s);

/*
****	Fonction des sons
*/
void						create_sounds(t_sdl *sdl);
void						play_music(t_main *s);

/*
****	Fonction de temps
*/
void						ft_set_time(t_main *s);
void						ft_fps(t_main* s);

/*
****	Fonction de l'editeur
*/
void						display_map(t_main *s);
void						get_grid_tab(t_main *s);
void						ft_draw_editor(t_editor *edi, t_texture *tex);
void						mouse_grid(t_main *s, t_pos save);

/*
****	Fonction de gestion d'images
*/
void						update_image(t_main *s, t_texture *texture);
void						draw_rect(t_texture *text, t_dpos orig,
	t_dpos dest, Uint32 color);
void						set_pixel(t_texture *text, Uint32 color, t_pos coord);
Uint32						get_pixel_color(t_texture *text, int x, int y);
void						draw_player(t_main *s, t_dpos p_pos);
void						draw_wall(t_main *s, t_pos ori);
t_image						*load_tga(char *path, int i, int idx, int ret);
void						draw_image(t_texture *texture, t_pos ori,
	t_pos dest, t_image *image);
void						draw_space_menu(t_main *s);
void						draw_editor_menu(t_main *s, double perx,
	short orig_x, short orig_y);

/*
****	Fonction de creation de ligne
*/
int							trace_line(t_main *s, Uint32 color, int w);
void						trace_vertical(t_main *s, Uint32 color, int w);
void						get_line(t_main *s, Uint32 color, int w);
void						ft_draw_all_wall(t_main *s);

/*
****	Fonction de gestion des controls
*/
int							keyboard_controls(t_main *s, int key);
void						editor_handler(t_main *s);
void						event_handler(t_main *s);
void						handle_keys(t_main *s);
void						change_mode(t_main *s, int key);
int							ft_prev_next_floor(t_main *s, char prev_next);
void						move_editor(t_main *s, const Uint8 *keys);
void						ft_crouch(t_main *s, const Uint8 *keys);
void						ft_jump(t_main *s, const Uint8 *keys);
void						change_weapon(t_main *s, int up);
void						ft_fly_mode(t_main *s, const Uint8 *keys);
void						ft_activ_fly(t_main *s);
void 						fly(t_main *s);
void						ft_transition(t_main *s);

/*
****	Fonction de gestion et de protection du parsing
*/
int							ft_parsing(t_main *s, int fd);
int							ft_find_next_number(char *str, int i);
void						ft_check_validity_last_sector(t_main *s);
int							ft_check_wall_that_intersect(t_main *s,
							t_sector *sct_in_check);
void						ft_check_move_vertex_validity(t_main *s, int id);
t_pos						ft_find_polygon_center(t_sector *sct);
int							ft_check_sector_sens(t_main *s, t_sector *sct);
int							ft_check_wall_lenght(t_sector *sct);
int							is_dest_valid(t_main *s, int id);
void						add_portal_ptr(t_main *s, t_int *wall, int i);
void						ft_norm_parse_sector(t_main *s, char *line, t_sector *sct, int i);
void						ft_parsing_norm(t_main *s, char *line, int i, int y);

/*
****	Fonction de gestion des listes chainés
*/
int							ft_add_vertex(t_main *s, int x, int y);
int							ft_check_vertex(t_main *s, int x, int y);
t_sector					*ft_add_sector(t_main *s, int floor, int ceiling);
int							ft_add_intarray(t_main *s, t_sector *sector,
							int value, t_int *tmp);
void						put_wall_value(t_sector *sector, char *line, int i);
void						ft_test_chainlist(t_main *s);
t_int						*get_t_int_by_vertex_id(t_int *vtx, int ptr_id);

/*
****	Fonction de gestion des vecteurs
*/
void						draw_anchor(t_main *s, t_pos ori, Uint32 color);
void						create_anchor(t_main *s, t_pos ori);
int							anchor_exists(t_main *s, t_pos ori);
void						set_selected(t_main *s, t_pos ori, char on);
t_pos						get_abs_pos(t_main *s, t_pos ori);
void						move_anchor(t_main *s, int id);
void						remove_anchor(t_main *s, int id);
int							remove_sector(t_main *s, int id, int del, int sct_id);
void						ft_reset_color_vertex(t_main *s);

/*
****	Fonction de gestion des secteurs
*/
int							ft_parse_sector(t_main *s, char *line);
int							ft_sector_mode(t_main *s, int x, int y);
void						fill_sectors(t_main *s);
void						draw_sector(t_main *s, int x, int y, Uint32 r_color);
t_int						*free_sector_struct(t_sector *temp_sector);
void						remove_sprite(t_main *s, int id);
void						remove_sprite_from_sector(t_main *s, t_sprite *sprite);
int							get_nearest_sector(t_main *s, t_pos pos, t_pos *new_pos);
int							handle_sector_zero(t_main *s);

/*
****	Fonction de gestion des portails
*/
void						change_over_wall(t_main *s);
void						edit_portal(t_main *s);
void						remove_portal(t_main *s);
void						reset_temp_portals(t_main *s);
t_dpos						ft_get_fake_player(t_main *s, t_dpos player, t_int *vtx, double *angle_fake, double prev_angle);
t_visu						get_walls_to_draw(t_main *s, t_dpos player, t_visu vs);
void						add_portal_to_list(t_main *s, t_dpos player,
							t_sector *sct, t_visu vs);
void						check_map_portals(t_main *s);
int							check_portal_validity(t_main *s, t_int *vtx, t_visu *vs);
int							check_portal_validity_player(t_main *s, t_int *vtx, t_visu *vs);

/*
****	Fonction utilitaire
*/
int							arround(int space, int nb);
double						angle_mod(double angle);
t_pos						get_px_pos(t_main *s, t_pos ref);
// void						empiler(t_main *s, t_pile *pile, t_pos new_pixel);
// t_pos						depiler(t_pile *pile);
int							ft_is_in_sector(t_main *s, t_dpos point_2);
int							ft_find_intersection(t_main *s, t_4dpos pos, char visu);
t_dpos						ft_find_coord(t_abpos l1, t_abpos l2);
t_pos						ft_dpos_to_pos(t_dpos dpos);
t_dpos						ft_pos_to_dpos(t_pos pos);
void						ft_reset_color_screen(Uint32 *str, int size);
double						to_rad(double angle);
double						to_degres(double rad);
double						percent(double value, double total);
t_sector					*get_sector_by_id(t_main *s, int id);
t_vertex					*get_vertex_by_id(t_main *s, int id);
t_int						*get_t_int_by_id(t_int *obj, int id);
double						ft_dist_t_dpos(t_dpos pos1, t_dpos pos2);
double						ft_dist_t_pos(t_pos pos1, t_pos pos2);
t_dpos						to_edi_coord(t_main *s, t_dpos coord);
int							clamp (int x, int min, int max);
void						ft_zoom(t_main *s, t_pos pos, int space);
int							max(int value1, int value2);
int							min(int value1, int value2);
double						ft_find_angle_plan(double a, double b, double c);
double						vxs(double x1, double y1, double x2, double y2);
int							ft_is_in_segment(t_dpos coord, t_dpos begin, t_dpos end);
void						ft_trace_vertical_select(t_main *s, t_line line,
	Uint32 color);
int							ft_trace_line_select(t_main *s, t_line line, Uint32 color);
void						ft_get_line_select(t_main *s, t_line line, Uint32 color);
void						trace_select(t_main *s);
void						remove_selected_anchor(t_main *s);

/*
****	Fonction de gestion du joueur
*/
void						set_player(t_main *s);
//void						ft_move_player(t_main *s, const Uint8 *key);
t_dpos						get_direction(t_main *s, const Uint8 *keys, double speed,
	t_dpos target);
void						ft_move_player(t_main *s, const Uint8 *keys,
	int move_speed);
void						rotate_player(t_main *s, const Uint8 *keys);
void						teleport_player(t_main *s, const unsigned char *keys);
void						ft_trace_vertical(t_main *s, t_line line, Uint32 color);
void						ft_get_line(t_main *s, t_line line, Uint32 color);
int							ft_trace_line(t_main *s, t_line line, Uint32 color);
void						trace_direction(t_main *s);
void						rotate_mouse(t_main *s);
// void						draw_weapon(t_main *s, double perx, short orig_x, short orig_y);
void						draw_hud(t_main *s);
void						display_hud(t_main *s, int i, int j, int px);
void						shoot(t_main *s);
void						display_crosshair(t_main *s, int i, int j, t_image *wp);
// void						draw_weapon2(t_main *s, int i, int j);
int							is_colliding(t_main *s, t_dpos target, int sct_id);
void 						check_collectible(t_main *s);
void						tp_first_sector(t_main *s);

/*
****	Fonction de sauvegarde
*/
void						ft_save_map(t_main *s);
void						ft_click_save(t_main *s);
void						ft_add_letter_to_savemap(t_main *s, int key);
void						ft_del_letter_to_savemap(t_main *s);
void						ft_save_msg(t_main *s, int error);
void						ft_write_file(t_main *s);

/*
****	Fonction des ttf
*/
void						ft_create_ttf(t_ttf ttf, t_main *s, TTF_Font *police);
void						ft_init_font(t_main *s);
void						ft_draw_ttf_play(t_main *s);
void						ft_draw_ttf_editor(t_main *s);
void						ft_display_message(t_main *s);
void						ft_create_message(t_main *s, int color, int duration, char *str);
void						ft_init_msg(t_main *s);
char						*get_jetpack_value(t_main *s);

/*
****	Fonction de debug
*/
void						print_wall_list(t_main *s);
void 						print_player_values(t_main *s);
void						draw_sprite_hitbox(t_main *s);
void						ft_print_sprite_list(t_main *s);
void						ft_print_sectors_sprites(t_main *s);

/*
****	Fonction des textures
*/
void						display_sky(t_main *s, int px, int j, double value);
void						ft_draw_floor(t_main *s, t_walls *wall, t_pos coord);
int							ft_draw_ceiling(t_main *s, t_walls *wall, t_pos coord);
void 						draw_texture(t_multithread *mt, t_pos coord, int end);
void						get_total_w_wall(t_walls *wall);
void 						change_wall_texture(t_main *s, int up);
void						ft_draw_column(t_pos coord, int end, t_multithread *mt);

/*
****	Fonction sprite chainlist
*/
t_pos						get_px_r_pos(t_main *s, t_dpos ref);
void						*ft_memalloc(size_t size);
void						add_sprite(t_main *s, t_dpos pos, int idimg);
void						draw_sprite(t_main *s, double angle, t_sprite *sprite);
void 						display_sprites(t_main *s);
void 						unset_sprites(t_main *s);
void 						set_visible_sprites(t_main *s, t_visu *vs);
int							check_sprite_menu_click(t_main *s, t_pos pos);
void						draw_sprite_menu(t_main *s);
void						display_sprite_inverse(t_main *s, double angle,
	t_sprite *cur);

void						free_sprite(t_main *s);
void						free_lsprite(t_main *s);
void						free_anim(t_anim anim);
// void						free_lanim(t_lanim *anim);

void						remove_sprite_by_id(t_main *s, int id);
// void						remove_sprite_by_select(t_main *s);
// void						remove_sprite(t_main *s, t_sprite *cur, t_sprite *next,
	// t_sprite *prev);

t_dpos						get_abs_r_pos(t_main *s, t_pos ori);
/*
****	Fonction sprite Yohann
*/
t_sprite					*create_new_sprite(t_main *s, t_name name, t_dpos pos);
void 						get_sprite_info_by_name(t_main *s, t_name name, t_sprite *sprite);
t_sprite					*is_sprite_under_mouse(t_main *s);
int							is_sprite_selected(t_main *s);
void 						display_sprite_menu(t_main *s);
void 						select_sprite_type(t_main *s);
void						remove_selected_sprite(t_main *s);
void						move_sprite(t_main *s);
void 						draw_sprites_ori(t_main *s);
void						set_sprite(t_main *s);
void 						add_sprite_to_sector(t_main *s, t_sprite *sprite);
void 						draw_plain_sprite(t_main *s, t_pos coord, t_image *img, t_texture *tex);
int							check_if_visible(t_main *s, t_sprite *sprite);
void						print_sprite(t_main *s, t_sprite *farthest);
void 						check_bomb(t_main *s);

/*
****	Fonction mode selection
*/
void						select_vertex(t_main *s);
void						deselect_vertex(t_main *s);
void						move_vertex(t_main *s, t_pos tmp_mosve, t_pos ori, int id);
int							exist_vertex(t_main *s, t_pos *mouse_save, int *id,
	t_pos *ori);
void						reset_id(t_main *s);
int							found_id_sprite(t_main *s, t_pos start, t_pos end);

void						deselect_sprite(t_main *s);
int							select_sprite(t_main *s);
int							set_selected_sprite(t_main *s, t_pos *mouse_save);

void						display_chainlist(t_main *s);

int							check_exist(t_main *s, t_dpos target, int id);
void						fire(t_main *s);
// void    sprite_move(t_main *s);
void						sprite_move_on_player(t_main *s, t_sprite *cur);
void						ia(t_main*s, t_sprite *cur);

void						rand_move(t_main *s, double angle, t_sprite *sprite);

/*
****	Fonction animations
*/
void						kill(t_sprite *cur);
void						play_sprites_anims(t_main *s);
void 						enemy_walk_anim(t_main *s, t_sprite *sprite);

// void						sprite_shooting(t_main *s, t_sprite *cur);
void						kill_anim(t_main *s, t_sprite *cur);
void						set_img(t_main *s, t_sprite *cur, int id, int orientation);
void 						destroy_planet(t_main *s);
void						load_anims(t_main *s);
t_anim_enemy 				load_storm_anim(t_main *s);
t_anim						load_face_storm(t_anim data);
t_anim						load_back_storm(t_anim data);
t_anim						load_prof_storm(t_anim data);
void						fill_texture_list(t_main *s);
void						animate_weapon(t_main *s);
void						select_weapon_anim(t_main *s);

void 						select_anim(t_main *s, t_sprite *sprite);
void						play_g_o_anim(t_main *s);
/*
****	Fonction geston des armes
*/

void 						set_weapon_range(t_main *s);

/*
****	Fonction IA
*/
void 						sprite_shooting(t_main *s, t_sprite *sprite);
int							is_player_shot(t_main *s, t_sprite *sprite);
#endif
