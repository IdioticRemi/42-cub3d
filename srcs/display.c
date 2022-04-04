/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:51 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 18:48:40 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_to_win(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->player.image.ptr, cub->player.x * TILE_SIZE,
		cub->player.y * TILE_SIZE);
}

void	put_player_pixel(t_cub *cub)
{
	mlx_pixel_put(cub->mlx, cub->win, cub->player.x_start * TILE_SIZE, cub->player.y_start * TILE_SIZE, 0xff0000);
}


void	put_map_to_win(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{		
			mlx_put_image_to_window(cub->mlx, cub->win,
				cub->tile.space.ptr, j * TILE_SIZE, i * TILE_SIZE);
			if (cub->map.array[i][j] == '1')
				mlx_put_image_to_window(cub->mlx, cub->win,
					cub->tile.wall.ptr, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
}
