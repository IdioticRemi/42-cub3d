
#include "cub3d.h"

void	free_map_arr(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.row_count)
	{
		free(cub->map.array[i]);
		i++;
	}
	free(cub->map.array);
}
