#include "cub3d.h"

void	get_side_dist_and_step(t_ray *ray, t_player *player)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_distX = (player->pos.x - ray->mapX) * ray->delta_distX;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distX = (ray->mapX + 1.0 - player->pos.x) * ray->delta_distX;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_distY = (player->pos.y - ray->mapY) * ray->delta_distY;
	}
	else
	{
		ray->step_y = 1;
		ray->side_distY = (ray->mapY + 1.0 - player->pos.y) * ray->delta_distY;
	}
}

void	dda_algo(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_distX < ray->side_distY)
		{
printf("[x] sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
			ray->side_distX += ray->delta_distX;
			ray->mapX += ray->step_x;
			ray->side_hit = 0;
printf("[x]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
		}
		else
		{
printf("[y]sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

			ray->side_distY += ray->delta_distY;
			ray->mapY += ray->step_y;
			ray->side_hit = 1;
printf("[y]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

		}
		if (map->array[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
}

void	get_start_and_end(t_cub *cub, t_ray *ray)
{
	
	cub->info.line_height = (int)(cub->win_height / ray->perpWallDist);
	cub->info.draw_start = (-cub->info.line_height / 2) + (cub->win_height / 2);
	if (cub->info.draw_start < 0)
			cub->info.draw_start = 0;
	cub->info.draw_end = (cub->info.line_height / 2) + (cub->win_height / 2);
	if (cub->info.draw_end >= cub->win_height)
		cub->info.draw_end = cub->win_height - 1;
}

void	set_color(t_cub *cub, t_ray *ray)
{
	if (cub->map.array[ray->mapX][ray->mapY] == 1)
		cub->info.color = PINK;
	else if (cub->map.array[ray->mapX][ray->mapY] == 2)
		cub->info.color = RED;
	else if (cub->map.array[ray->mapX][ray->mapY] == 3)
		cub->info.color = YELLOW;
	else if (cub->map.array[ray->mapX][ray->mapY] == 4)
		cub->info.color = GRAY;
	else
		cub->info.color = WHITE;
	if (ray->side_hit == 1)
		cub->info.color = cub->info.color / 2;
}

void	raycaster(t_cub *cub, t_fov *fov)
{
	int	x;
	t_ray ray;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		fov->cameraX = ((2 * x) / (float)SCREEN_WIDTH) - 1;
		ray.dir.x = fov->dir.x + fov->plane.x * fov->cameraX;
		ray.dir.y = fov->dir.y + fov->plane.y * fov->cameraX;
		ray.mapX = (int)(cub->player.pos.x);
		ray.mapY = (int)(cub->player.pos.y);

		// ray.delta_distX = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
		// ray.delta_distY = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));

		ray.delta_distX = fabs(1 / ray.dir.x);
		ray.delta_distY = fabs(1 / ray.dir.y);
		ray.hit = 0;

		get_side_dist_and_step(&ray, &cub->player);
		dda_algo(&ray, &cub->map);
		if (ray.side_hit == 0)
			ray.perpWallDist = (ray.mapX - cub->player.pos.x + (1 - ray.step_x) / 2) / ray.dir.x;
		else
			ray.perpWallDist = (ray.mapY - cub->player.pos.y + (1 - ray.step_y) / 2) / ray.dir.y;
		get_start_and_end(cub, &ray);
		set_color(cub, &ray);
		draw_vertical_line(cub, x, cub->info.draw_start, cub->info.draw_end, cub->info.color);
		x++;
	}
}