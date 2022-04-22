#include "cub3d.h"

void	player_get_coord(t_cub *cub)
{	
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{
			if (cub->map.array[i][j] == 'N'
				||cub->map.array[i][j] == 'S'
				||cub->map.array[i][j] == 'W'
				||cub->map.array[i][j] == 'E')
			{
				cub->player.start_dir = cub->map.array[i][j];
				cub->player.pos = set_vector(j, i);
			}
			j++;
		}
		i++;
	}
}
