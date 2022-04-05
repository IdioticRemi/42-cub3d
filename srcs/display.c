/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:51 by selee             #+#    #+#             */
/*   Updated: 2022/04/05 17:10:13 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_to_win(t_cub *cub)
{
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->player.image.ptr, cub->player.x,
		cub->player.y);
}

void	put_player_pixel(t_cub *cub)
{
	mlx_pixel_put(cub->mlx, cub->win, cub->player.x, cub->player.y, YELLOW);
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

void	put_map_grid(t_cub *cub)
{
	int		i;
	int		j;

	i = 1;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j <= cub->win_width)
		{
			mlx_pixel_put(cub->mlx, cub->win, j, i * (cub->win_height / cub->map.row_count), WHITE);
			j++;
		}
		i++;
	}
	i = 1;
	while (i < cub->map.column_count)
	{
		j = 0;
		while (j <= cub->win_height)
		{
			mlx_pixel_put(cub->mlx, cub->win, i * (cub->win_width / cub->map.column_count), j, WHITE);
			j++;
		}
		i++;
	}
}
