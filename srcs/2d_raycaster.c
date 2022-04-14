#include "cub3d.h"

void	draw_line(t_cub *cub, int x, int start, int end, int color)
{
	int		y;
	y = start;
	while (y <= end)
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
		p.pos_x += cub->player.dir_x; 
		p.pos_y += cub->player.dir_y;
		mlx_pixel_put(cub->mlx, cub->win, p.dir_x, p.dir_y, BLUE);
	}

}
