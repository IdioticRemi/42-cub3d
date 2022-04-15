#include "cub3d.h"

void	rotate_left(t_cub *cub)
{
	t_fov f;
	f = cub->fov;

	cub->fov.dir.x = f.dir.x * cos(-f.rotate_speed) - f.dir.y * sin(-f.rotate_speed);
	cub->fov.dir.y = f.dir.y * sin(-f.rotate_speed) + f.dir.y * cos(-f.rotate_speed);
	// printf("dirX: %f | dirY: %f\n", cub->fov.dir.x, cub->fov.dir.y);
}

void	rotate_right(t_cub *cub)
{
	t_fov f;
	f = cub->fov;

	cub->fov.dir.x = f.dir.x * cos(f.rotate_speed) - f.dir.y * sin(f.rotate_speed);
	cub->fov.dir.y = f.dir.y * sin(f.rotate_speed) + f.dir.y * cos(f.rotate_speed);
	// printf("dirX: %f | dirY: %f\n", cub->fov.dir.x, cub->fov.dir.y);
}