#include "cub3d.h"

/*
void	set_ray_values(t_cub *cub, int x)
{
	cub->fov.cameraX = (2 * x / (float)(cub->win_width)) - 1;

	cub->ray.dir.x = cub->fov.dir.x + cub->fov.plane.x * cub->fov.cameraX;
	cub->ray.dir.y = cub->fov.dir.y + cub->fov.plane.y * cub->fov.cameraX;
	cub->ray.mapX = (int)(cub->player.pos.x);
	cub->ray.mapY = (int)(cub->player.pos.y);

	cub->ray.delta_distX = sqrt(1 + (cub->ray.dir.y * cub->ray.dir.y) / (cub->ray.dir.x * cub->ray.dir.x));
	cub->ray.delta_distY = sqrt(1 + (cub->ray.dir.x * cub->ray.dir.x) / (cub->ray.dir.y * cub->ray.dir.y));

	cub->ray.hit = 0;
}
*/

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
	cub->texture.line_height = (int)(cub->win_height / ray->perpWallDist);

	cub->texture.draw_start = (-cub->texture.line_height / 2) + (cub->win_height / 2);
	if (cub->texture.draw_start < 0)
			cub->texture.draw_start = 0;
	cub->texture.draw_end = (cub->texture.line_height / 2) + (cub->win_height / 2);
	if (cub->texture.draw_end >= cub->win_height)
		cub->texture.draw_end = cub->win_height - 1;
}

void	set_color(t_cub *cub, t_ray *ray)
{
	if (cub->map.array[ray->mapX][ray->mapY] == 1)
		cub->texture.color = PINK;
	else if (cub->map.array[ray->mapX][ray->mapY] == 2)
		cub->texture.color = RED;
	else if (cub->map.array[ray->mapX][ray->mapY] == 3)
		cub->texture.color = YELLOW;
	else if (cub->map.array[ray->mapX][ray->mapY] == 4)
		cub->texture.color = GRAY;
	else
		cub->texture.color = WHITE;
	if (ray->side_hit == 1)
		cub->texture.color = cub->texture.color / 2;
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
// printf("[ray.dir]x: %f | y: %f | [delta]x: %f | y: %f\n", ray.dir.x, ray.dir.y, ray.delta_distX, ray.delta_distY);
// printf("dirX: %f | dirY: %f | mapX: %d | mapY: %d\n", ray.dir.x, ray.dir.y, ray.mapX, ray.mapY);	
		get_side_dist_and_step(&ray, &cub->player);
		dda_algo(&ray, &cub->map);
		if (ray.side_hit == 0)
			ray.perpWallDist = (ray.mapX - cub->player.pos.x + (1 - ray.step_x) / 2) / ray.dir.x;
		else
			ray.perpWallDist = (ray.mapY - cub->player.pos.y + (1 - ray.step_y) / 2) / ray.dir.y;
		get_start_and_end(cub, &ray);
		set_color(cub, &ray);
		draw_vertical_line(cub, x, cub->texture.draw_start, cub->texture.draw_end, cub->texture.color);
		x++;
	}
}