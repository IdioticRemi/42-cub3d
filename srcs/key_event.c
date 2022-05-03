#include "cub3d.h"

void	rotate(t_cub *cub, float rot_angle)
{
	cub->cam.yaw += rot_angle;
}


int	key_movement(t_cub *cub, int keycode)
{
	t_vect	direction;

	direction = set_vector(cub->cam.yaw + FOV / 2, cub->cam.yaw + FOV / 2);
	if (keycode == KEY_S)
		direction = vector_add(direction, set_vector(PI, PI));
	if (keycode == KEY_A)
		direction = vector_subs(direction, set_vector(PI / 2, PI / 2));
	if (keycode == KEY_D)
		direction = vector_add(direction, set_vector(PI / 2, PI / 2));
	if (keycode == KEY_W || keycode == KEY_S || keycode == KEY_A || keycode == KEY_D)
	{
		direction = set_vector(cos(direction.x), sin(direction.y));
		direction = vector_multi(direction, MOVE_SPEED);
		cub->player.pos = vector_add(cub->player.pos, direction);
	}
	if (keycode == KEY_LEFT)
		rotate(cub, -ROTATE_SPEED);
	if (keycode == KEY_RIGHT)
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