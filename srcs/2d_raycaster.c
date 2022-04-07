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

// void	cast_rays(t_cub *cub)
// {
// 	int i = 0;

// 	while (i < )
// 	draw_line(cub, cub->player.dir_x, cub->player.dir_y, cub->player.dir_y + 50, GREEN);

// }

void	put_ray(t_cub *cub)
{
	t_player	p;
	p = cub->player;

	while (cub->map.array[(int)(p.pos_y / TILE_SIZE)][(int)(p.pos_x / TILE_SIZE)] != '1')
	{
		p.pos_x += cos(p.dir_x);
		p.pos_y += sin(p.dir_y);
		mlx_pixel_put(cub->mlx, cub->win, p.pos_x, p.pos_y, GREEN);
	}
}