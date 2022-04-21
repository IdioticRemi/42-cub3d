#include "cub3d.h"

void	rotate(t_cub *cub, float rot_angle)
{
	t_fov	f;
	f = cub->fov;
	cub->fov.dir.x = f.dir.x * cos(rot_angle) - f.dir.y * sin(rot_angle);
	cub->fov.dir.y = f.dir.x * sin(rot_angle) + f.dir.y * cos(rot_angle);
}

int	key_movement(t_cub *cub, int keycode)
{
	if (cub->status == GAME_PLAY)
	{
		if (keycode == KEY_W)
			cub->player.pos.y--;
		else if (keycode == KEY_S)
			cub->player.pos.y++;
		else if (keycode == KEY_A)
			cub->player.pos.x--;
		else if (keycode == KEY_D)
			cub->player.pos.x++;
		else if (keycode == KEY_LEFT)
			rotate(cub, -cub->fov.rot_angle);
		else if (keycode == KEY_RIGHT)
			rotate(cub, cub->fov.rot_angle);
	}
	return (0);
}

int	key_press(t_cub *cub, int key)
{
	if (key == KEY_W)
	{
		if (!cub->map.array[(int)(cub->player.pos.x + cub->fov.dir.x * cub->fov.move_speed)][(int)(cub->player.pos.y)])
			cub->player.pos.x += cub->fov.dir.x * cub->fov.move_speed;
		if (!cub->map.array[(int)(cub->player.pos.x)][(int)(cub->player.pos.y + cub->fov.dir.y * cub->fov.move_speed)])
			cub->player.pos.y += cub->fov.dir.y * cub->fov.move_speed;
	}
	if (key == KEY_S)
	{
		if (!cub->map.array[(int)(cub->player.pos.x - cub->fov.dir.x * cub->fov.move_speed)][(int)(cub->player.pos.y)])
			cub->player.pos.x -= cub->fov.dir.x * cub->fov.move_speed;
		if (!cub->map.array[(int)(cub->player.pos.x)][(int)(cub->player.pos.y - cub->fov.dir.y * cub->fov.move_speed)])
			cub->player.pos.y -= cub->fov.dir.y * cub->fov.move_speed;
	}
	return 0;
}

int	key_input(int keycode, t_cub *cub)
{
	if (cub->status == GAME_PLAY)
		// key_press(cub, keycode);
		key_movement(cub, keycode);
	if (keycode == KEY_ESC)
	{
		free_map_arr(cub);
		exit(EXIT_SUCCESS);
	}
	return (0);
}