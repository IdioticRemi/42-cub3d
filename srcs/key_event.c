#include "cub3d.h"

int	key_input(int keycode, t_cub *cub)
{
	if (cub->status == GAME_PLAY)
	{
		if (keycode == KEY_W || keycode == KEY_UP)
			move_to_directions(cub, DIR_NO);
		else if (keycode == KEY_S || keycode == KEY_DOWN)
			move_to_directions(cub, DIR_SO);
		else if (keycode == KEY_A || keycode == KEY_LEFT)
			move_to_directions(cub, DIR_WE);
		else if (keycode == KEY_D || keycode == KEY_RIGHT)
			move_to_directions(cub, DIR_EA);
	}

	if (keycode == KEY_ESC)
	{
		free_map_arr(cub);
		exit(0);
	}
	return (0);
}
