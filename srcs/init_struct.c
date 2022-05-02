#include "cub3d.h"

void	init_struct_map(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map._array = NULL;
	cub->map.row_count = 0;
	cub->map.column_count = 0;
}

static void	init_camera(t_cub *cub, char dir)
{
	if (dir == 'N')
		cub->cam.yaw = 0;
	else if (dir == 'W')
		cub->cam.yaw = PI / 2;
	else if (dir == 'S')
		cub->cam.yaw = PI;
	else if (dir == 'E')
		cub->cam.yaw = PI / 2 * 3;
	else
		cub->cam.yaw = 0;
}

void	init_player(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{
			if (ft_strchr("NSWE", cub->map.array[i][j]))
			{
				cub->player.pos = set_vector(j * TILE_SIZE + TILE_SIZE / 2, i * TILE_SIZE + TILE_SIZE / 2);
				init_camera(cub, cub->map.array[i][j]);
			}
			j++;
		}
		i++;
	}
}

void	init_game(t_cub *cub)
{
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	init_player(cub);
	cub->screen.ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT); //create new image of the screen itself
	cub->screen.addr = mlx_get_data_addr(cub->screen.ptr, 
		&cub->screen.bits_per_pixel, &cub->screen.line_length, &cub->screen.endian);
}
