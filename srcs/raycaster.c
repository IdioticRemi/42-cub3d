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
	
	while (cub->map.array[(int)(p.pos_y / TILE_SIZE)][(int)(p.pos_x / TILE_SIZE)] != '1')
	{
		p.pos_x += cub->fov.dir_x;
		p.pos_y += cub->fov.dir_y;
		mlx_pixel_put(cub->mlx, cub->win, p.pos_x, p.pos_y, PINK);
	}
}

void	display_fov(t_cub *cub)
{
	t_fov	f;
	f = cub->fov;

	f.x += cub->ray.dir_x;
	f.y += cub->ray.dir_y;
	mlx_pixel_put(cub->mlx, cub->win, f.x, f.y, BLUE);

}

void	raycaster(t_cub *cub)
{
	for (int x = 0; x < cub->win_width / 2; x++)
	{
		float cameraX = 2 * x / (float)cub->win_width - 1;
		printf("cameraX: %f\n", cameraX);
		cub->ray.dir_x = cub->fov.dir_x + cub->fov.plane_x * cameraX;
		cub->ray.dir_y = cub->fov.dir_y + cub->fov.plane_y * cameraX;

		int	mapX = cub->player.x_start;
		int	mapY = cub->player.y_start;

		cub->ray.delta_distX = fabs( 1 / cub->ray.dir_x); //fabs(); gets absolute value of the argument
		cub->ray.delta_distY = fabs( 1 / cub->ray.dir_y);

		if (cub->ray.dir_x < 0)
		{
			cub->ray.step_x = -1;
			cub->ray.side_distX = (cub->player.x_start - mapX) * cub->ray.delta_distX;
		}
		else
		{
			cub->ray.step_x = 1;
			cub->ray.side_distX = (mapX + 1.0 - cub->player.x_start) * cub->ray.delta_distX;
		}
		if (cub->ray.dir_y < 0)
		{
			cub->ray.step_y = -1;
			cub->ray.side_distY = (cub->player.y_start - mapY) * cub->ray.delta_distY;
		}
		else
		{
			cub->ray.step_y = 1;
			cub->ray.side_distY = (mapY + 1.0 - cub->player.y_start) * cub->ray.delta_distY;
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
			cub->ray.perpWallDist = (mapX - cub->player.x_start + (1 - cub->ray.step_x) / 2) / cub->ray.dir_x;
		else
			cub->ray.perpWallDist = (mapY - cub->player.y_start + (1 - cub->ray.step_y) / 2) / cub->ray.dir_y;
	
		display_fov(cub);

		int lineHeight = (int)(cub->win_height / cub->ray.perpWallDist);

		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int	drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;
	}
}