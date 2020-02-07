#include "doom.h"

int		ft_how_many_pipe(char *str)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (str[i] != '\0')
	{
		if (str[i++] == '|')
			pipe++;
	}
	return (pipe);
}

int		ft_parse_ennemi_part2(t_main *s, char *line, int i, t_sprite *sprite)
{
	if (!sprite)
		return (0);
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	sprite->s_angle = (double)ft_atoi(&line[i]);
	i += ft_longlen((int)sprite->s_angle) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	sprite->name = ft_atoi(&line[i]);
	get_sprite_info_by_name(s, sprite->name, sprite);
	return (0);
}

int		ft_parse_ennemi(t_main *s, char *line)
{
	t_sprite	*sprite;
	t_dpos		pos;
	t_type		type;
	int			i;

	if ((i = ft_find_next_number(line, 0)) == -1)
		handle_error(s, MAP_ERROR);
	type = ft_atoi(&line[i]);
	i += ft_longlen(type) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	pos.x = ft_atoi(&line[i]);
	i += ft_longlen((int)pos.x) + 1;
	if ((i = ft_find_next_number(line, i)) == -1)
		handle_error(s, MAP_ERROR);
	pos.y = ft_atoi(&line[i]);
	i += ft_longlen((int)pos.y) + 1;
	pos.x /= 100;
	pos.y /= 100;
	sprite = create_new_sprite(s, 0, pos, s->sprite);
	ft_parse_ennemi_part2(s, line, i, sprite);
	return (0);
}

void	ft_parsing_norm(t_main *s, char *line, int i, int y)
{
	if (line[0] == 'V')
	{
		y = ft_atoi(&line[i]);
		i += ft_longlen(y) + 1;
		ft_add_vertex(s, ft_atoi(&line[i]), y);
	}
	else if (line[0] == 'S' && ft_how_many_pipe(line) == 3)
	{
		ft_parse_sector(s, line);
		ft_check_validity_last_sector(s);
	}
	else if (line[0] == 'E' && ft_how_many_pipe(line) == 3)
		ft_parse_ennemi(s, line);
	else if (line[0] == 'P')
	{
		s->player.r_ori.y = (float)ft_atoi(&line[i]) / METRE;
		i += ft_longlen(s->player.r_ori.y * METRE);
		if ((i = ft_find_next_number(line, i)) == -1)
			handle_error(s, MAP_ERROR);
		s->player.r_ori.x = (float)ft_atoi(&line[i]) / METRE;
		s->player.r_pos = s->player.r_ori;
	}
}
