#include "cub3d.h"

void	rotate(t_cub *cub, float rot_angle)
{
	cub->cam.yaw += rot_angle;
}

int	key_press_event(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->keys.key_w = 1;
	if (keycode == KEY_S)
		cub->keys.key_s = 1;
	if (keycode == KEY_A)
		cub->keys.key_a = 1;
	if (keycode == KEY_D)
		cub->keys.key_d = 1;
	if (keycode == KEY_RIGHT)
		cub->keys.key_right = 1;
	if (keycode == KEY_LEFT)
		cub->keys.key_left = 1;
	if (keycode == KEY_ESC)
	{
		free_map_arr(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	key_release_event(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->keys.key_w = 0;
	if (keycode == KEY_S)
		cub->keys.key_s = 0;
	if (keycode == KEY_A)
		cub->keys.key_a = 0;
	if (keycode == KEY_D)
		cub->keys.key_d = 0;
	if (keycode == KEY_RIGHT)
		cub->keys.key_right = 0;
	if (keycode == KEY_LEFT)
		cub->keys.key_left = 0;
	return (0);
}

void	handle_movement(t_cub *cub)
{
	t_vect	movement;

	if (cub->keys.key_w || cub->keys.key_s || cub->keys.key_a || cub->keys.key_d)
	{
		movement = collision_handler(cub);
		cub->player.pos = vector_add(cub->player.pos, movement);
	}
	if (cub->keys.key_left)
		rotate(cub, -ROTATE_SPEED);
	if (cub->keys.key_right)
		rotate(cub, ROTATE_SPEED);
}
