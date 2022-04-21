#include "cub3d.h"

void	draw_line(t_cub *cub, int x, int y1, int y2, int color)
{
	int		y;
	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
		y++;
	}
}

void	put_ray(t_cub *cub)
{
	t_player	p;
	p = cub->player; 
	
	while (cub->map.array[(int)(p.pos.y / GRID_SIZE)][(int)(p.pos.x / GRID_SIZE)] != '1')
	{
		p.pos.x += cub->fov.dir.x;
		p.pos.y += cub->fov.dir.y;
		mlx_pixel_put(cub->mlx, cub->win, p.pos.x, p.pos.y, PINK);
	}
}

void	vertical_line(t_cub *cub, int x, int y_start, int y_end, int color)
{
	int		y;
	y = y_start;
	while (y < y_end)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
		y++;
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

		if (cub->ray.dir.x < 0)
		{
			cub->ray.step_x = -1;
			cub->ray.side_distX = (cub->player.pos.x - mapX) * cub->ray.delta_distX;
		}
		else
		{
			cub->ray.step_x = 1;
			cub->ray.side_distX = (mapX + 1.0 - cub->player.pos.x) * cub->ray.delta_distX;
		}
		if (cub->ray.dir.y < 0)
		{
			cub->ray.step_y = -1;
			cub->ray.side_distY = (cub->player.pos.y - mapY) * cub->ray.delta_distY;
		}
		else
		{
			cub->ray.step_y = 1;
			cub->ray.side_distY = (mapY + 1.0 - cub->player.pos.y) * cub->ray.delta_distY;
		}

		while (cub->ray.hit == 0)
		{
			if (cub->ray.side_distX < cub->ray.side_distY)
			{
				cub->ray.side_distX += cub->ray.delta_distX;
				mapX += cub->ray.step_x;
				cub->ray.side_hit = 0;
			}
			else
			{
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
	
		int lineHeight = (int)(cub->win_height / cub->ray.perpWallDist);

		int drawStart = (-lineHeight / 2) + (cub->win_height / 2);
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = (lineHeight / 2) + (cub->win_height / 2);
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;

		int color;
		if (cub->map.array[mapX][mapY] == 1)
			color = BLUE;
		// else if (cub->map.array[mapX][mapY] == 2)
		// 	color = 0x00FF00;
		// else if (cub->map.array[mapX][mapY] == 3)
		// 	color = 0x0000FF;
		// else if (cub->map.array[mapX][mapY] == 4)
		// 	color = 0xFFFFFF;
		else
			color = BLACK;

		//明るさ調整
		if (cub->ray.side_hit == 1)
			color = color / 2;
		draw_line(cub, x, drawStart, drawEnd, color);
		x++;
	}
}
