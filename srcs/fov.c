#include "cub3d.h"

t_vect	set_fov_direction(t_cub *cub)
{
	t_vect ret;

	ret = cub->fov.dir;
	if (cub->player.start_dir == 'N')
		ret = set_vector(0.0, -1.0);
	else if (cub->player.start_dir == 'S')
		ret = set_vector(0.0, 1.0);
	else if (cub->player.start_dir == 'W')
		ret = set_vector(-1.0, 0.0);
	else if (cub->player.start_dir == 'E')
		ret = set_vector(1.0, 0.0);
	return (ret);
}

t_vect	set_fov_plane(t_cub *cub, int width)
{
	float	min;

	min = tan(cub->fov.angle/2) / width * 2;
	if (cub->player.start_dir == 'E')
		return (set_vector(0, -min));
	else if (cub->player.start_dir == 'N')
		return (set_vector(min, 0));
	else if (cub->player.start_dir == 'W')
		return (set_vector(0, min));
	return (set_vector(min, 0));
}

