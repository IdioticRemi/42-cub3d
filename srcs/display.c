/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:51 by selee             #+#    #+#             */
/*   Updated: 2022/04/21 03:50:12 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_pixel(t_cub *cub)
{
	mlx_pixel_put(cub->mlx, cub->win, cub->player.pos.x, cub->player.pos.y, RED);
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
				cub->tile.space.ptr, j * GRID_SIZE, i * GRID_SIZE);
			if (cub->map.array[i][j] == '1')
				mlx_put_image_to_window(cub->mlx, cub->win,
					cub->tile.wall.ptr, j * GRID_SIZE, i * GRID_SIZE);
			j++;
		}
		i++;
	}
}

void	put_map_grid(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j <= cub->win_width)
		{
			mlx_pixel_put(cub->mlx, cub->win, j, i * (cub->win_height / cub->map.row_count), GRAY);
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
			mlx_pixel_put(cub->mlx, cub->win, i * (cub->win_width / cub->map.column_count), j, GRAY);
			j++;
		}
		i++;
	}
}
