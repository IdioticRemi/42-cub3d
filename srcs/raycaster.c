#include "cub3d.h"


void	calculate_side_distance(t_ray *ray, t_player *player, int mapX, int mapY)
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

void	raycaster(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < cub->win_width)
	{
		float	cameraX = (2 * x / (float)(cub->win_width)) - 1;
		cub->ray.dir.x = cub->fov.dir.x + cub->fov.plane.x * cameraX;
		cub->ray.dir.y = cub->fov.dir.y + cub->fov.plane.y * cameraX;

		int	mapX = (int)(cub->player.pos.x);
		int	mapY = (int)(cub->player.pos.y);
		
		cub->ray.delta_distX = fabs( 1 / cub->ray.dir.x);
		cub->ray.delta_distY = fabs( 1 / cub->ray.dir.y);

		cub->ray.hit = 0;
		
		calculate_side_distance(&cub->ray, &cub->player, mapX, mapY);

		while (cub->ray.hit == 0)
		{
		printf("sidedistX: %f | sidedistY: %f\n", cub->ray.side_distX, cub->ray.side_distY);
			if (cub->ray.side_distX < cub->ray.side_distY)
			{
				cub->ray.side_distX += cub->ray.delta_distX;
				mapX += cub->ray.step_x;
				cub->ray.side_hit = 0;
			}
			else
			{
				printf("check\n");
				cub->ray.side_distY += cub->ray.delta_distY;
				mapY += cub->ray.step_y;
				cub->ray.side_hit = 1;
			}
			if (cub->map.array[mapX][mapY] > 0)
				cub->ray.hit = 1;
		}

		if (cub->ray.side_hit == 0)
			cub->ray.perpWallDist = (mapX - cub->player.pos.x + (1 - cub->ray.step_x) / 2) / cub->ray.dir.x;
		else
			cub->ray.perpWallDist = (mapY - cub->player.pos.y + (1 - cub->ray.step_y) / 2) / cub->ray.dir.y;


printf("posX: %f | posY: %f | raydirX: %f | raydirY: %f\n", cub->player.pos.x, cub->player.pos.y, cub->ray.dir.x, cub->ray.dir.y);
		int lineHeight = (int)(cub->win_height / cub->ray.perpWallDist);
printf("lineheight: %d | perpWall: %f | mapX: %d | mapY: %d\n", lineHeight, cub->ray.perpWallDist, mapX, mapY);
		int drawStart = (-lineHeight / 2) + (cub->win_height / 2);
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = (lineHeight / 2) + (cub->win_height / 2);
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;

		int color;
		if (cub->map.array[mapX][mapY] == 1)
			color = BLUE;
		else if (cub->map.array[mapX][mapY] == 2)
			color = 0x00FF00;
		else if (cub->map.array[mapX][mapY] == 3)
			color = 0x0000FF;
		else if (cub->map.array[mapX][mapY] == 4)
			color = 0xFFFFFF;
		else
			color = BLACK;

		//明るさ調整
		if (cub->ray.side_hit == 1)
			color = color / 2;
// printf("start: %d | end: %d\n", drawStart, drawEnd);
		draw_vertical_line(cub, x, drawStart, drawEnd, color);
		x++;
	}
}
