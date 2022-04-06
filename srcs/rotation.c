#include "cub3d.h"

void	rotate_left(t_cub *cub)
{
	cub->player.angle -= 0.1;
	if (cub->player.angle < 0)
		cub->player.angle += 2 * PI;
	cub->player.delta_x = cos(cub->player.angle * 5);
	cub->player.delta_y = sin(cub->player.angle * 5);
}

void	rotate_right(t_cub *cub)
{
	cub->player.angle += 0.1;
	if (cub->player.angle > 2 * PI)
		cub->player.angle -= 2 * PI;
	cub->player.delta_x = cos(cub->player.angle * 5);
	cub->player.delta_y = sin(cub->player.angle * 5);
}
