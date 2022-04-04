#include "cub3d.h"

int	game_loop(t_cub *cub)
{
	// if (cub->status == GAME_START)
	// 	put_start_messsage(cub);
	if (cub->status == GAME_PLAY)
	{
		put_map_to_win(cub);
		// put_player_to_win(cub);
		// put_step_count_to_win(cub);
		// collec_is_collected(cub);
		// player_at_exit(cub);
	}
	// else if (cub->status == GAME_CONTINUE)
	// 	put_continue_messsage(cub);
	// else if (cub->status == GAME_END)
	// 	put_end_messsage(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	char		*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	cub.status = GAME_START;
	map_check_file_extension(map_path, ".ber");
	map_read_and_check(&cub, map_path);
	init_game(&cub);
	init_game_img (&cub);
	// mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, &key_input, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	// mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, 0);
	mlx_loop(cub.mlx);
}
