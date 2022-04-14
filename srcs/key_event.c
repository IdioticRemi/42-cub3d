#include "cub3d.h"

int	key_movement(t_cub *cub, int keycode)
{
	if (cub->status == GAME_PLAY)
	{
		if (keycode == KEY_W)
			move_to_directions(cub, DIR_NO);
		else if (keycode == KEY_S)
			move_to_directions(cub, DIR_SO);
		else if (keycode == KEY_A)
			move_to_directions(cub, DIR_WE);
		else if (keycode == KEY_D)
			move_to_directions(cub, DIR_EA);
		else if (keycode == KEY_LEFT)
			rotate_left(cub);
		else if (keycode == KEY_RIGHT)
			rotate_right(cub);
	}
	return (0);
}

int	key_input(int keycode, t_cub *cub)
{
	if (cub->status == GAME_PLAY)
		key_movement(cub, keycode);
	if (keycode == KEY_ESC)
	{
		free_map_arr(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}