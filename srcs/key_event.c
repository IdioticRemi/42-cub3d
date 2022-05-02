#include "cub3d.h"

void	rotate(t_cub *cub, float rot_angle)
{
	cub->cam.yaw += rot_angle;
}


int	key_movement(t_cub *cub, int keycode)
{
	if (keycode == KEY_W)
		cub->player.pos.y -= MOVE_SPEED;
	else if (keycode == KEY_S)
		cub->player.pos.y += MOVE_SPEED;
	else if (keycode == KEY_A)
		cub->player.pos.x -= MOVE_SPEED;
	else if (keycode == KEY_D)
		cub->player.pos.x += MOVE_SPEED;
	else if (keycode == KEY_LEFT)
		rotate(cub, -ROTATE_SPEED);
	else if (keycode == KEY_RIGHT)
		rotate(cub, ROTATE_SPEED);
	return (0);
}

int	key_input(int keycode, t_cub *cub)
{

	key_movement(cub, keycode);
	if (keycode == KEY_ESC)
	{
		free_map_arr(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}