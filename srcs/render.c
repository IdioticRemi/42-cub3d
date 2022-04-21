#include "cub3d.h"

void	draw_vertical_line(t_cub *cub, int x, int y1, int y2, int color)
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

