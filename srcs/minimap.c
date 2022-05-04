/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:34:14 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 16:35:37 by selee            ###   ########lyon.fr   */
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

void	draw_minimap(t_cub *cub, int shift_x, int shift_y, char obstacle)
{
	int		a;
	int		b;

	a = -1;
	while (++a < TILE_SIZE * MINIMAP_SCALE)
	{
		b = -1;
		while (++b < TILE_SIZE * MINIMAP_SCALE)
		{
			if (obstacle)
				mlx_img_pixel_put(cub, shift_x + a, shift_y + b, BLACK);
			else
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
			obstacle = cub->map.array[x][y] == '1';
			draw_minimap(cub, shift_x, shift_y, obstacle);
		}
	}
}
