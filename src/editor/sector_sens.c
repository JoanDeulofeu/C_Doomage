#include "doom.h"

void	ft_score_se(t_int *wall, double *score_se)
{
	if (wall->ptr->x * METRE > wall->next->ptr->x * METRE)
		*score_se += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->x * METRE < wall->next->ptr->x * METRE)
		*score_se -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_so(t_int *wall, double *score_so)
{
	if (wall->ptr->y * METRE > wall->next->ptr->y * METRE)
		*score_so += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->y * METRE < wall->next->ptr->y * METRE)
		*score_so -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_ne(t_int *wall, double *score_ne)
{
	if (wall->ptr->y * METRE < wall->next->ptr->y * METRE)
		*score_ne += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->y * METRE > wall->next->ptr->y * METRE)
		*score_ne -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_no(t_int *wall, double *score_no)
{
	if (wall->ptr->x * METRE < wall->next->ptr->x * METRE)
		*score_no += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->x * METRE > wall->next->ptr->x * METRE)
		*score_no -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

int		ft_verify_sens(t_sector *sct, t_4double score)
{
	int	i;
	int	nb_secur;

	i = 0;
	nb_secur = (sct->vertex->prev->id == 3) ? 2 : 3;
	// printf("------------\n");
	if (score.d1 > 0)
	{
		i++;
		// printf("-no");
	}
	if (score.d2 > 0)
	{
		i++;
		// printf("-ne");
	}
	if (score.d3 > 0)
	{
		i++;
		// printf("-so");
	}
	if (score.d4 > 0)
	{
		i++;
		// printf("-se");
	}
	if (i >= nb_secur)
	{
		// printf("\nsector sens OK\n\n");
		return (0);
	}
	// printf("\nsector sens KO\n\n");
	return (1);
}

int		ft_check_sector_sens(t_main *s, t_sector *sct)
{
	t_pos		center;
	t_4double	score;
	t_int		*wall;
	int			i;

	(void)s;
	center = ft_find_polygon_center(sct);
	printf("sct n%d center = x(%d) y(%d)\n", sct->id, center.x, center.y);
	wall = sct->vertex;
	printf("vtx x(%d) y(%d)\n", wall->ptr->x * METRE, wall->ptr->y * METRE);
	wall = wall->next;
	while (wall != sct->vertex)
	{
		printf("vtx x(%d) y(%d)\n", wall->ptr->x * METRE, wall->ptr->y * METRE);
		wall = wall->next;
	}
	wall = sct->vertex;
	i = 0;
	score.d1 = 0.0;
	score.d2 = 0.0;
	score.d3 = 0.0;
	score.d4 = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		if (wall->ptr->x * METRE < center.x)
		{
			if (wall->ptr->y * METRE < center.y)
				ft_score_no(wall, &score.d1);
			else if (wall->ptr->y * METRE >= center.y)
				ft_score_so(wall, &score.d3);
		}
		else if (wall->ptr->x * METRE > center.x)
		{
			if (wall->ptr->y * METRE <= center.y)
				ft_score_ne(wall, &score.d2);
			else if (wall->ptr->y * METRE > center.y)
				ft_score_se(wall, &score.d4);
		}
		else if (wall->ptr->x * METRE == center.x)
		{
			if (wall->ptr->y * METRE <= center.y)
				ft_score_no(wall, &score.d1);
			else if (wall->ptr->y * METRE > center.y)
				ft_score_se(wall, &score.d4);
		}
		wall = wall->next;
	}
	return (ft_verify_sens(sct, score));
}
