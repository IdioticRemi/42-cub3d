#include "cub3d.h"

// void	put_player_to_win(t_cub *cub)
// {
// 	mlx_put_image_to_window(cub->mlx, cub->win,
// 		cub->player.image.ptr, cub->player.x * TILE_SIZE,
// 		cub->player.y * TILE_SIZE);
// }

void	put_map_to_win(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{		
			mlx_put_image_to_window(cub->mlx, cub->win,
				cub->tile.space.ptr, j * TILE_SIZE, i * TILE_SIZE);
			if (cub->map.array[i][j] == '1')
				mlx_put_image_to_window(cub->mlx, cub->win,
					cub->tile.wall.ptr, j * TILE_SIZE, i * TILE_SIZE);
			// if (cub->map.array[i][j] == 'E')
			// 	mlx_put_image_to_window(cub->mlx, cub->win,
			// 		cub->tile.exit.ptr, j * TILE_SIZE, i * TILE_SIZE);
			// if (cub->map.array[i][j] == 'C')
			// 	mlx_put_image_to_window(cub->mlx, cub->win,
			// 		cub->collec.image.ptr, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}

// void	put_start_messsage(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (cub->map.column_count / 3) * TILE_SIZE;
// 	y = (cub->map.row_count / 2) * TILE_SIZE;
// 	mlx_string_put(cub->mlx, cub->win, x, y, 0xFFFFFF, "PRESS SPACE TO START");
// }

// void	put_continue_messsage(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (cub->map.column_count / 3) * TILE_SIZE;
// 	y = (cub->map.row_count / 2) * TILE_SIZE;
// 	mlx_string_put(cub->mlx, cub->win, x, y, 0x000000,
// 		"COLLECT ALL COOKIES: PRESS SPACE TO RESUME");
// }

// void	put_end_messsage(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	x = (cub->map.column_count / 3) * TILE_SIZE;
// 	y = (cub->map.row_count / 2) * TILE_SIZE;
// 	mlx_string_put(cub->mlx, cub->win, x, y, 0x000000,
// 		"GAME CLEAR: PRESS ESC TO QUIT");
// }
