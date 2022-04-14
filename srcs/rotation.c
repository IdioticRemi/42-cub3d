#include "cub3d.h"

void	rotate_left(t_cub *cub)
{
	t_player p;
	p = cub->player;

	cub->player.dir_x = p.dir_x * cos(-p.rotate_speed) - p.dir_y * sin(-p.rotate_speed);
	cub->player.dir_y = p.dir_y * sin(-p.rotate_speed) + p.dir_y * cos(-p.rotate_speed);
	printf("dirX: %f | dirY: %f\n", cub->player.dir_x, cub->player.dir_y);
}

void	rotate_right(t_cub *cub)
{
	t_player p;
	p = cub->player;

	cub->player.dir_x = p.dir_x * cos(p.rotate_speed) - p.dir_y * sin(p.rotate_speed);
	cub->player.dir_y = p.dir_y * sin(p.rotate_speed) + p.dir_y * cos(p.rotate_speed);
	printf("dirX: %f | dirY: %f\n", cub->player.dir_x, cub->player.dir_y);

}