#include "cub3d.h"

void	test_parsing(t_cub *cub)
{
	cub->info.floor = GREEN;
	cub->info.ceiling = BLUE;
	
	cub->info.n_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.s_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.w_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.e_path = ft_strdup("./assets_xpm/black_square32.xpm");

	cub->map.column_count = 8;
	cub->map.row_count = 8;

	cub->map._array = ft_strdup("11111111101N0001100001111000000111100001100000011001000111111111");
	cub->map.array = malloc(sizeof(char *) * cub->map.column_count);

	for (int i = 0; i < cub->map.column_count; i++)
	{
		cub->map.array[i] = &cub->map._array[i * cub->map.column_count];
	}

	for (int i = 0; i < cub->map.column_count; i++)
	{
		for (int j = 0; j < cub->map.row_count; j++)
		{
			ft_putchar_fd(cub->map.array[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

int	game_loop(t_cub *cub)
{
	draw_background(cub);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	char		*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	test_parsing(&cub);
	init_game(&cub);
	// map_check_file_extension(map_path, ".cub");
	// map_read_and_check(&cub, map_path);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, &key_input, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, 0);
	mlx_loop(cub.mlx);
}
