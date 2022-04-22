#include "cub3d.h"

int	game_loop(t_cub *cub)
{
	if (cub->status == GAME_PLAY)
	{
		put_map_to_win(cub);
		put_map_grid(cub);
		put_player_pixel(cub);
		// put_horizontal_line(cub);
		put_ray(cub);
		raycaster(cub);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char		*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	cub.status = GAME_PLAY;
	init_struct(&cub);
	map_check_file_extension(map_path, ".ber");
	map_read_and_check(&cub, map_path);
	init_game(&cub);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, &key_input, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, 0);
	mlx_loop(cub.mlx);
}
