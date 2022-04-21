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
	for (int x = 0; x < cub->win_width; x++)
	{
		float cameraX = 2 * x / ((float)cub->win_width) - 1;
		cub->ray.dir.x = cub->fov.dir.x + cub->fov.plane.x * cameraX;
		cub->ray.dir.y = cub->fov.dir.y + cub->fov.plane.y * cameraX;

		int	mapX = cub->player.start_grid.x;
		int	mapY = cub->player.start_grid.y;

		cub->ray.delta_distX = fabs( 1 / cub->ray.dir.x);
		cub->ray.delta_distY = fabs( 1 / cub->ray.dir.y);

		if (cub->ray.dir.x < 0)
		{
			cub->ray.step_x = -1;
			cub->ray.side_distX = (cub->player.start_grid.x - mapX) * cub->ray.delta_distX;
		}
		else
		{
			cub->ray.step_x = 1;
			cub->ray.side_distX = (mapX + 1.0 - cub->player.start_grid.x) * cub->ray.delta_distX;
		}
		if (cub->ray.dir.y < 0)
		{
			cub->ray.step_y = -1;
			cub->ray.side_distY = (cub->player.start_grid.y - mapY) * cub->ray.delta_distY;
		}
		else
		{
			cub->ray.step_y = 1;
			cub->ray.side_distY = (mapY + 1.0 - cub->player.start_grid.y) * cub->ray.delta_distY;
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
			cub->ray.perpWallDist = (mapX - cub->player.start_grid.x + (1 - cub->ray.step_x) / 2) / cub->ray.dir.x;
		else
			cub->ray.perpWallDist = (mapY - cub->player.start_grid.y + (1 - cub->ray.step_y) / 2) / cub->ray.dir.y;
	
		int lineHeight = (int)(cub->win_height / cub->ray.perpWallDist);

		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;
	}
}