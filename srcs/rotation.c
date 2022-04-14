#include "cub3d.h"

void	rotate_left(t_cub *cub)
{
	t_fov f;
	f = cub->fov;

	cub->fov.dir_x = f.dir_x * cos(-f.rotate_speed) - f.dir_y * sin(-f.rotate_speed);
	cub->fov.dir_y = f.dir_y * sin(-f.rotate_speed) + f.dir_y * cos(-f.rotate_speed);
	printf("dirX: %f | dirY: %f\n", cub->fov.dir_x, cub->fov.dir_y);
}

void	rotate_right(t_cub *cub)
{
	t_fov f;
	f = cub->fov;

	cub->fov.dir_x = f.dir_x * cos(f.rotate_speed) - f.dir_y * sin(f.rotate_speed);
	cub->fov.dir_y = f.dir_y * sin(f.rotate_speed) + f.dir_y * cos(f.rotate_speed);
	printf("dirX: %f | dirY: %f\n", cub->fov.dir_x, cub->fov.dir_y);

}