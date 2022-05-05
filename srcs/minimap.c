/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:34:14 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 14:27:23 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	render_map(t_cub *cub)
// {
// 	for (int x = 0; x < cub->map.column_count; x++)
// 	{
// 		for (int y = 0; y < cub->map.row_count; y++)
// 		{
// 			int shift_x = x * TILE_SIZE * MINIMAP_SCALE;
// 			int shift_y = y * TILE_SIZE * MINIMAP_SCALE;
// 			char tile = cub->map.array[x][y];
// 			char obstacle = tile == '1';
// 			for (int a = 0; a < TILE_SIZE * MINIMAP_SCALE; a++)
// 			{
// 				for (int b = 0; b < TILE_SIZE * MINIMAP_SCALE; b++)
// 				{
// 					if (obstacle)
// 						mlx_img_pixel_put(cub, shift_x + a, shift_y + b, BLACK);
// 					else
// 						mlx_img_pixel_put(cub, shift_x + a, shift_y + b, WHITE);
// 				}
// 			}
// 		}
// 	}
// }
void	bresenham(t_cub *cub, t_vect src, t_vect dest, int color)
{
	double	step_x;
	double	step_y;
	int		i;

	step_x = dest.x - src.x;
	step_y = dest.y - src.y;
	i = fmax(fabs(step_x), fabs(step_y));
	step_x /= i;
	step_y /= i;
	while ((int)(src.x - dest.x) || (int)(src.y - dest.y))
	{
		if (!(src.x >= SCREEN_WIDTH || src.y >= SCREEN_HEIGHT
				|| src.x < 0 || src.y < 0))
		{
			mlx_img_pixel_put(cub, src.x, src.y, color);
			mlx_img_pixel_put(cub, src.x, src.y + 1, color);
			mlx_img_pixel_put(cub, src.x + 1, src.y, color);
		}
		src.x += step_x;
		src.y += step_y;
	}
}

void	put_point(t_cub *cub, t_vect crd, int color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 8)
	{
		y = -1;
		while (++y < 8)
		{
			if (!(crd.x + x - 4 < 0
					|| crd.x + x - 4 > SCREEN_WIDTH
					|| crd.y + y - 4 < 0
					|| crd.y + y - 4 > SCREEN_HEIGHT))
				mlx_img_pixel_put(cub, crd.x + x - 4, crd.y + y - 4, color);
		}
	}
}

void	draw_minimap(t_cub *cub, int shift_x, int shift_y, char obstacle)
{
	int		a;
	int		b;

	a = -1;
	while (++a < TILE_SIZE * MINIMAP_SCALE - 1)
	{
		b = -1;
		while (++b < TILE_SIZE * MINIMAP_SCALE - 1)
		{
			if (obstacle == '1')
				mlx_img_pixel_put(cub, shift_x + a, shift_y + b, BLACK);
			else if (obstacle == '0')
				mlx_img_pixel_put(cub, shift_x + a, shift_y + b, WHITE);
		}
	}
}

void	render_minimap(t_cub *cub)
{
	int		x;
	int		y;
	int		shift_x;
	int		shift_y;
	char	obstacle;

	x = -1;
	while (++x < cub->map.column_count)
	{
		y = -1;
		while (++y < cub->map.row_count)
		{
			shift_x = x * TILE_SIZE * MINIMAP_SCALE;
			shift_y = y * TILE_SIZE * MINIMAP_SCALE;
			obstacle = cub->map.array[x][y];
			draw_minimap(cub, shift_x, shift_y, obstacle);
		}
	}
}
