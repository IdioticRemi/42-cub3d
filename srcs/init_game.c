#include "cub3d.h"

void	init_map_value(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map.row_count = 0;
	cub->map.column_count = 0;
}

// void	init_player_value(t_cub *cub)
// {
// 	cub->player.move_count = 0;
// }

void	init_mlx_and_win(t_cub *cub)
{
	int	size_x;
	int	size_y;

	size_x = cub->map.column_count * TILE_SIZE;
	size_y = cub->map.row_count * TILE_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, size_x, size_y, "so_long");
}

void	init_game(t_cub *cub)
{
	// init_player_value(cub);
	init_mlx_and_win(cub);
}
