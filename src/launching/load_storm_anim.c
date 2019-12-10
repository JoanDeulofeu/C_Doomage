#include "doom.h"

t_anim				load_face_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/face/standing.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/face/walking1.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/face/walking2.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/face/walking3.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/face/walking4.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/face/walking5.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/face/walking6.tga",
		0, 0, 0);
	// data.image[7] = data.image[5];
	// data.image[8] = data.image[4];
	// data.image[9] = data.image[3];
	// data.image[10] = data.image[2];
	return (data);
	// data->max_current = 6;
}

t_anim				load_back_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/back/standing.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/back/walking1.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/back/walking2.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/back/walking3.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/back/walking4.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/back/walking5.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/back/walking6.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 6;
}

t_anim				load_prof_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/prof/standing.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/prof/walking1.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/prof/walking2.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/prof/walking3.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/prof/walking4.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/prof/walking5.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/prof/walking6.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 6;
}

t_anim				load_prof_back_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/profback/standing.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/profback/walking1.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/profback/walking2.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/profback/walking3.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/profback/walking4.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/profback/walking5.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/profback/walking6.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 6;
}

t_anim				load_prof_face_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/profface/standing.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/profface/walking1.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/profface/walking2.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/profface/walking3.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/profface/walking4.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/profface/walking5.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/profface/walking6.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 6;
}

t_anim				load_dying_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/dying/dying1.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/dying/dying2.tga",
		0, 0, 0);
	data.image[2] = load_tga("images/ressources/trooper/dying/dying3.tga",
		0, 0, 0);
	data.image[3] = load_tga("images/ressources/trooper/dying/dying4.tga",
		0, 0, 0);
	data.image[4] = load_tga("images/ressources/trooper/dying/dying5.tga",
		0, 0, 0);
	data.image[5] = load_tga("images/ressources/trooper/dying/dying6.tga",
		0, 0, 0);
	data.image[6] = load_tga("images/ressources/trooper/dying/dying7.tga",
		0, 0, 0);
	data.image[7] = load_tga("images/ressources/trooper/dying/dying8.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 4;
}

t_anim				load_shooting_storm(t_anim data)
{
	data.image[0] = load_tga("images/ressources/trooper/shooting/shoot1.tga",
		0, 0, 0);
	data.image[1] = load_tga("images/ressources/trooper/shooting/shoot2.tga",
		0, 0, 0);
	return (data);
	// data->max_current = 1;
}

t_anim_enemy 		load_storm_anim(t_main *s)
{
	ft_bzero((void*)(&s->stormtrooper), sizeof(t_anim_enemy));
	s->stormtrooper.face = load_face_storm(s->stormtrooper.face);
	s->stormtrooper.back = load_back_storm(s->stormtrooper.back);
	s->stormtrooper.prof = load_prof_storm(s->stormtrooper.prof);
	s->stormtrooper.prof_back = load_prof_back_storm(s->stormtrooper.prof_back);
	s->stormtrooper.prof_face = load_prof_face_storm(s->stormtrooper.prof_face);
	s->stormtrooper.dying = load_dying_storm(s->stormtrooper.dying);
	s->stormtrooper.shooting = load_shooting_storm(s->stormtrooper.shooting);
	return (s->stormtrooper);
}