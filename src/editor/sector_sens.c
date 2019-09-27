#include "doom.h"

void	ft_score_se(t_int *wall, double *score_se)
{
	if (wall->ptr->pos.x > wall->next->ptr->pos.x)
		*score_se += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->pos.x < wall->next->ptr->pos.x)
		*score_se -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_so(t_int *wall, double *score_so)
{
	if (wall->ptr->pos.y < wall->next->ptr->pos.y)
		*score_so += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->pos.y > wall->next->ptr->pos.y)
		*score_so -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_ne(t_int *wall, double *score_ne)
{
	if (wall->ptr->pos.y < wall->next->ptr->pos.y)
		*score_ne += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->pos.y > wall->next->ptr->pos.y)
		*score_ne -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

void	ft_score_no(t_int *wall, double *score_no)
{
	if (wall->ptr->pos.x < wall->next->ptr->pos.x)
		*score_no += ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
	else if (wall->ptr->pos.x > wall->next->ptr->pos.x)
		*score_no -= ft_dist_t_pos(wall->ptr->pos, wall->next->ptr->pos);
}

int		ft_verify_sens(double score1, double score2, double score3, double score4)
{
	int i;

	i = 0;
	if (score1 > 0)
		i++;
	if (score2 > 0)
		i++;
	if (score3 > 0)
		i++;
	if (score4 > 0)
		i++;
	if (i >= 3)
	{
		// printf("sector sens OK\n");
		return (0);
	}
	// printf("sector sens KO\n");
	return (1);
}

int		ft_check_sector_sens(t_main *s, t_sector *sct)
{
	(void)s;
	t_pos	center;
	double	score_no;
	double	score_ne;
	double	score_so;
	double	score_se;
	t_int	*wall;
	int		i;

	center = ft_find_polygon_center(sct);
	wall = sct->vertex;
	i = 0;
	score_no = 0.0;
	score_ne = 0.0;
	score_so = 0.0;
	score_se = 0.0;
	while (i++ < sct->vertex->prev->id)
	{
		if (wall->ptr->pos.x < center.x)
		{
			if (wall->ptr->pos.y < center.y)
				ft_score_no(wall, &score_no);
			else if (wall->ptr->pos.y >= center.y)
				ft_score_so(wall, &score_so);
		}
		else if (wall->ptr->pos.x > center.x)
		{
			if (wall->ptr->pos.y <= center.y)
				ft_score_ne(wall, &score_ne);
			else if (wall->ptr->pos.y > center.y)
				ft_score_se(wall, &score_se);
		}
		else if (wall->ptr->pos.x == center.x)
		{
			if (wall->ptr->pos.y <= center.y)
				ft_score_no(wall, &score_no);
			else if (wall->ptr->pos.y > center.y)
				ft_score_se(wall, &score_se);
		}
		wall = wall->next;
	}
	return (ft_verify_sens(score_no, score_ne, score_so, score_se));
}
