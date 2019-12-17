#include "doom.h"

void	load_skybox(t_main *s)
{
	s->skybox.image[0] = load_tga("images/skybox_00.tga", 0, 0, 0);
	s->skybox.image[1] = load_tga("images/skybox_01.tga", 0, 0, 0);
	s->skybox.image[2] = load_tga("images/skybox_02.tga", 0, 0, 0);
	s->skybox.image[3] = load_tga("images/skybox_03.tga", 0, 0, 0);
	s->skybox.image[4] = load_tga("images/skybox_04.tga", 0, 0, 0);
	s->skybox.image[5] = load_tga("images/skybox_05.tga", 0, 0, 0);
	s->skybox.image[6] = load_tga("images/skybox_06.tga", 0, 0, 0);
	s->skybox.image[7] = load_tga("images/skybox_07.tga", 0, 0, 0);
	s->skybox.image[8] = load_tga("images/skybox_08.tga", 0, 0, 0);
	s->skybox.image[9] = load_tga("images/skybox_09.tga", 0, 0, 0);
	s->skybox.image[10] = load_tga("images/skybox_10.tga", 0, 0, 0);
	s->skybox.image[11] = load_tga("images/skybox_11.tga", 0, 0, 0);
	s->skybox.image[12] = load_tga("images/skybox_12.tga", 0, 0, 0);
	s->skybox.image[13] = load_tga("images/skybox_13.tga", 0, 0, 0);
	s->skybox.image[14] = load_tga("images/skybox_14.tga", 0, 0, 0);
	s->skybox.image[15] = load_tga("images/skybox_15.tga", 0, 0, 0);
	s->skybox.image[16] = load_tga("images/skybox_16.tga", 0, 0, 0);
	s->skybox.image[17] = load_tga("images/skybox_17.tga", 0, 0, 0);
}

void	load_items(t_main *s)
{
	s->items.table.image[0] = load_tga("images/ressources/static/table.tga", 0, 0, 0);
	s->items.lamp.image[0] = load_tga("images/ressources/static/lamp.tga", 0, 0, 0);
	s->items.gun.image[0] = load_tga("images/ressources/static/gun.tga", 0, 0, 0);
	s->items.shotgun.image[0] = load_tga("images/ressources/static/shotgun.tga", 0, 0, 0);
	s->items.big_s_ammo.image[0] = load_tga("images/ressources/static/big_s_ammo.tga", 0, 0, 0);
	s->items.big_g_ammo.image[0] = load_tga("images/ressources/static/big_g_ammo.tga", 0, 0, 0);
}

void	fill_sprite_list(t_main *s)
{
	t_name	name;

	name = storm;
	s->editor->all_sprite.image[storm] = s->stormtrooper.face.image[0];
	s->editor->all_sprite.image[table] = s->items.table.image[0];
	s->editor->all_sprite.image[lamp] = s->items.lamp.image[0];
	s->editor->all_sprite.image[o_gun] = s->items.gun.image[0];
	s->editor->all_sprite.image[o_shotgun] = s->items.shotgun.image[0];
	s->editor->all_sprite.image[big_g_ammo] = s->items.big_g_ammo.image[0];
	s->editor->all_sprite.image[big_s_ammo] = s->items.big_s_ammo.image[0];
}

void	fill_texture_list(t_main *s)
{
	s->editor->all_texture.image[0] = load_tga("images/textures/02.tga", 0, 0, 0);
	s->editor->all_texture.image[1] = load_tga("images/textures/01.tga", 0, 0, 0);
	s->editor->all_texture.image[2] = load_tga("images/textures/03.tga", 0, 0, 0);
	s->editor->all_texture.image[3] = load_tga("images/textures/04.tga", 0, 0, 0);
	s->editor->all_texture.image[4] = load_tga("images/textures/05.tga", 0, 0, 0);
	s->editor->all_texture.image[5] = load_tga("images/textures/06.tga", 0, 0, 0);
	s->editor->all_texture.image[6] = load_tga("images/textures/07.tga", 0, 0, 0);
	s->editor->all_texture.image[7] = load_tga("images/textures/08.tga", 0, 0, 0);
	s->editor->all_texture.image[8] = load_tga("images/textures/09.tga", 0, 0, 0);
	s->editor->all_texture.image[9] = load_tga("images/textures/10.tga", 0, 0, 0);
	s->editor->all_texture.image[10] = load_tga("images/textures/11.tga", 0, 0, 0);
	s->editor->all_texture.image[11] = load_tga("images/textures/12.tga", 0, 0, 0);
}

void	load_anims(t_main *s)
{
	load_skybox(s);
	s->stormtrooper = load_storm_anim(s);
	load_items(s);
	s->wp_anims = load_wp_anims(s);
}
