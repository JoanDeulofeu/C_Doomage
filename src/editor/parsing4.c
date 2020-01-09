#include "doom.h"

int		ft_check_bar(char *str, int i)
{
	while ((str[i] < '0' || str[i] > '9') && str[i] != '|' && str[i] != '\0')
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

void	ft_put_texture_value(t_main *s, t_sector *sct, char *line, int i)
{
	t_int	*tmp;

	tmp = sct->vertex;
	if (tmp == NULL)
		return ;
	while (line[i] != '\0')
	{
		tmp->tex_nb = ft_atoi(&line[i]);
		tmp->image = s->editor->all_texture.image[tmp->tex_nb];
		i += ft_longlen(tmp->tex_nb);
		i = ft_find_next_number(line, i);
		if (i == -1)
			return ;
		tmp = tmp->next;
	}
}

int		ft_put_wall_value(t_sector *sct, char *line, int i)
{
	t_int	*tmp;

	tmp = sct->vertex;
	if (tmp == NULL)
		return (0);
	while (line[i] != '|' && line[i] != '\0')
	{
		tmp->wall_value = ft_atoi(&line[i]);
		i += ft_longlen(tmp->wall_value);
		if (ft_check_bar(line, i))
			break ;
		i = ft_find_next_number(line, i);
		if (i == -1)
			return (0);
		tmp = tmp->next;
	}
	return (i);
}

void	ft_norm_parse_sector(t_main *s, char *line, t_sector *sct, int i)
{
	int		value;

	value = 0;
	while (line[i] != '|' && line[i] != '\0')
	{
		value = ft_atoi(&line[i]);
		ft_add_intarray(s, sct, value, sct->vertex);
		i += ft_longlen(value) + 1;
		if (ft_check_bar(line, i))
			break ;
		i = ft_find_next_number(line, i);
	}
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	i = ft_put_wall_value(sct, line, i);
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	if (i)
		ft_put_texture_value(s, sct, line, i);
}

// void	ft_check_validity_last_sector(t_main *s)
// {
// 	t_sector	*sct;
// 	t_int		*wall;
//
// 	sct = s->sector;
// 	while (sct->next)
// 		sct = sct->next;
// 	wall = sct->vertex;
// 	if (wall->prev->id < 3 || sct->floor == sct->ceiling)
// 		remove_sector(s, wall->value, 0, 0);
// 	if (ft_check_wall_that_intersect(s, sct) || ft_check_sector_sens(s, sct))
// 		remove_sector(s, wall->value, 0, 0);
// 	if (ft_check_wall_lenght(sct) || sct->id > 100)
// 		remove_sector(s, wall->value, 0, 0);
// }

void	ft_check_validity_last_sector(t_main *s)
{
	t_sector	*sct;
	t_int		*wall;

	sct = s->sector;
	while (sct->next)
		sct = sct->next;
	wall = sct->vertex;
	if (wall->prev->id < 3 || sct->floor == sct->ceiling)
	{
		remove_sector(s, wall->value, 0, 0);
		printf("ERROR secteur non valide: moins de 3 vertex.\n");
	}
	if (ft_check_wall_that_intersect(s, sct))
	{
		remove_sector(s, wall->value, 0, 0);
		printf("ERROR secteur non valide: collision avec un autre secteur.\n");
	}
	if (ft_check_sector_sens(s, sct))
	{
		remove_sector(s, wall->value, 0, 0);
		printf("ERROR secteur non valide: sens du secteur non valide.\n");
	}
	if (ft_check_wall_lenght(sct))
	{
		remove_sector(s, wall->value, 0, 0);
		printf("ERROR secteur non valide: mur du secteur trop grand.\n");
	}
	if (sct->id > 100)
	{
		remove_sector(s, wall->value, 0, 0);
		printf("ERROR secteur non valide: Trop de secteur sur cette map.\n");
	}
}
