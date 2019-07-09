#include "doom.h"

int		ft_prev_next_floor(t_main *s, char prev_next)
{
	int			floor;
	int			block;
	t_sector	*sct;

	floor = s->editor->dply_floor;
	block = prev_next == 1 ? INT_MAX : INT_MIN;
	sct = s->sector;
	while (sct)
	{
		if (prev_next == 1)
		{
			if (sct->floor > floor && sct->floor < block)
				block = sct->floor;
		}
		else
		{
			if (sct->floor < floor && sct->floor > block)
				block = sct->floor;
		}
		sct = sct->next;
	}
	if (block == INT_MAX || block == INT_MIN)
		block = floor;
	// printf("block = %d\n", block);
	return (block);
}
