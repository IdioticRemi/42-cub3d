#include "cub3d.h"

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
	init_struct(&cub);
	map_check_file_extension(map_path, ".cub");
	map_read_and_check(&cub, map_path);
	init_game(&cub);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, &key_input, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, 0);
	mlx_loop(cub.mlx);
}




