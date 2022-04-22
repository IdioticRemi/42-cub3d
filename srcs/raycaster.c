#include "cub3d.h"

void	get_side_dist_and_step(t_ray *ray, t_player *player, int mapX, int mapY)
{
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_distX = (player->pos.x - mapX) * ray->delta_distX;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distX = (mapX + 1.0 - player->pos.x) * ray->delta_distX;
	}
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_distY = (player->pos.y - mapY) * ray->delta_distY;
	}
	else
	{
		ray->step_y = 1;
		ray->side_distY = (mapY + 1.0 - player->pos.y) * ray->delta_distY;
	}
}

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

void	get_distance(t_ray *ray, t_map *map)
{
	while (ray->hit == 0)
	{
		if (ray->side_distX < ray->side_distY)
		{
		printf("sideX 1: %f | mapX 1: %d\n", ray->side_distX, ray->mapX);
			ray->side_distX += ray->delta_distX;
			ray->mapX += ray->step_x;
			ray->side_hit = 0;
		printf("sideX 2: %f | mapX 2: %d\n", ray->side_distX, ray->mapX);
		
		}
		else
		{
			ray->side_distY += ray->delta_distY;
			ray->mapY += ray->step_y;
			ray->side_hit = 1;
		}
		if (map->array[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
}

void	get_start_and_end(t_cub *cub)
{
	cub->texture.line_height = (int)(cub->win_height / cub->ray.perpWallDist);

	cub->texture.draw_start = (-cub->texture.line_height / 2) + (cub->win_height / 2);
	if (cub->texture.draw_start < 0)
			cub->texture.draw_start = 0;
	cub->texture.draw_end = (cub->texture.line_height / 2) + (cub->win_height / 2);
	if (cub->texture.draw_end >= cub->win_height)
		cub->texture.draw_end = cub->win_height - 1;
}

void	set_color(t_cub *cub)
{
	if (cub->map.array[cub->ray.mapX][cub->ray.mapY] == 1)
		cub->texture.color = BLUE;
	else if (cub->map.array[cub->ray.mapX][cub->ray.mapY] == 2)
		cub->texture.color = RED;
	else if (cub->map.array[cub->ray.mapX][cub->ray.mapY] == 3)
		cub->texture.color = YELLOW;
	else if (cub->map.array[cub->ray.mapX][cub->ray.mapY] == 4)
		cub->texture.color = GRAY;
	else
		cub->texture.color = BLACK;

	if (cub->ray.side_hit == 1)
		cub->texture.color = cub->texture.color / 2;
}

void	raycaster(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		cub->fov.cameraX = (2 * x / (float)(cub->win_width)) - 1;

		cub->ray.dir.x = cub->fov.dir.x + cub->fov.plane.x * cub->fov.cameraX;
		cub->ray.dir.y = cub->fov.dir.y + cub->fov.plane.y * cub->fov.cameraX;
		cub->ray.mapX = (int)(cub->player.pos.x);
		cub->ray.mapY = (int)(cub->player.pos.y);

		cub->ray.delta_distX = sqrt(1 + (cub->ray.dir.y * cub->ray.dir.y) / (cub->ray.dir.x * cub->ray.dir.x));
		cub->ray.delta_distY = sqrt(1 + (cub->ray.dir.x * cub->ray.dir.x) / (cub->ray.dir.y * cub->ray.dir.y));
		cub->ray.hit = 0;
		get_side_dist_and_step(&cub->ray, &cub->player, cub->ray.mapX, cub->ray.mapY);		
		get_distance(&cub->ray, &cub->map);
		if (cub->ray.side_hit == 0)
			cub->ray.perpWallDist = (cub->ray.mapX - cub->player.pos.x + (1 - cub->ray.step_x) / 2) / cub->ray.dir.x;
		else
			cub->ray.perpWallDist = (cub->ray.mapY - cub->player.pos.y + (1 - cub->ray.step_y) / 2) / cub->ray.dir.y;
		get_start_and_end(cub);
		set_color(cub);
		draw_vertical_line(cub, x, cub->texture.draw_start, cub->texture.draw_end, cub->texture.color);
		x++;
	}
}
