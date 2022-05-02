#include "cub3d.h"

void	get_side_dist_and_step(t_dda *dda, t_player *player)
{
	if (dda->dir.x < 0)
	{
		dda->step_x = -1;
		dda->side_distX = (player->pos.x - dda->mapX) * dda->delta_distX;
	}
	else
	{
		dda->step_x = 1;
		dda->side_distX = (dda->mapX + 1.0 - player->pos.x) * dda->delta_distX;
	}
	if (dda->dir.y < 0)
	{
		dda->step_y = -1;
		dda->side_distY = (player->pos.y - dda->mapY) * dda->delta_distY;
	}
	else
	{
		dda->step_y = 1;
		dda->side_distY = (dda->mapY + 1.0 - player->pos.y) * dda->delta_distY;
	}
}

void	dda_algo(t_dda *dda, t_map *map)
{
	while (!dda->hit)
	{
		if (dda->side_distX < dda->side_distY)
		{
// printf("[x] sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
			dda->side_distX += dda->delta_distX;
			dda->mapX += dda->step_x;
			dda->side_hit = 0;
// printf("[x]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
		}
		else
		{
// printf("[y]sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

			dda->side_distY += dda->delta_distY;
			dda->mapY += dda->step_y;
			dda->side_hit = 1;
// printf("[y]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

		}
		if (map->array[dda->mapX][dda->mapY] > 0)
			dda->hit = 1;
	}
}

void	render_ray(t_cub *cub, int ray_index, t_dda dda)
{
	int x;
	int len;
	int i;
	int j;

	x = ray_index * STRIP_WIDTH;
	len = SCREEN_HEIGHT / dda.perpWallDist;

	i = -1;
	while (++i < STRIP_WIDTH)
	{
		j = -1;
		while (++j < len)
		{
			if (dda.side_hit == 0)
				mlx_img_pixel_put(cub, x + i, SCREEN_HEIGHT / 2 - len / 2 + j, RED);
			else
				mlx_img_pixel_put(cub, x + i, SCREEN_HEIGHT / 2 - len / 2 + j, PINK);
		}
	}
}

void	raycaster(t_cub *cub)
{
	int	x;
	float tempX;
	t_dda dda;

	x = 0;
	while (x < STRIP_COUNT)
	{
		tempX = ((float)x / ((float)STRIP_COUNT));
		dprintf(1, "%f | rad: %f\n", tempX, 2 * tempX * FOV - 1);
		dda.dir.x = cos(cub->cam.yaw + (2 * tempX * FOV - 1));
		dda.dir.y = sin(cub->cam.yaw + (2 * tempX * FOV - 1));
		dprintf(1, "%d | x: %f | y: %f\n", x, dda.dir.x, dda.dir.y);
		dda.mapX = cub->player.pos.x / TILE_SIZE;
		dda.mapY = cub->player.pos.y / TILE_SIZE;

		dda.delta_distX = sqrt(1 + (dda.dir.y * dda.dir.y) / (dda.dir.x * dda.dir.x));
		dda.delta_distY = sqrt(1 + (dda.dir.x * dda.dir.x) / (dda.dir.y * dda.dir.y));

		dda.hit = 0;

		get_side_dist_and_step(&dda, &cub->player);
		dda_algo(&dda, &cub->map);
		if (dda.side_hit == 0)
			dda.perpWallDist = (dda.mapX - cub->player.pos.x + (1 - dda.step_x) / 2) / dda.dir.x;
		else
			dda.perpWallDist = (dda.mapY - cub->player.pos.y + (1 - dda.step_y) / 2) / dda.dir.y;
		render_ray(cub, x, dda);
		x++;
	}
}
