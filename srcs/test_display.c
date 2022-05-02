/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:51 by selee             #+#    #+#             */
/*   Updated: 2022/05/02 14:00:51 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	put_player_pixel(t_cub *cub)
{
	mlx_pixel_put(cub->mlx, cub->win, cub->player.pos.x * TEXTURE_SIZE, cub->player.pos.y * TEXTURE_SIZE, RED);
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
				cub->texture.space.ptr, j * TEXTURE_SIZE, i * TEXTURE_SIZE);
			if (cub->map.array[i][j] == '1')
				mlx_put_image_to_window(cub->mlx, cub->win,
					cub->texture.wall.ptr, j * TEXTURE_SIZE, i * TEXTURE_SIZE);
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

void	put_ray(t_cub *cub)
{
	t_player	p;
	p = cub->player; 
	
	while (cub->map.array[(int)(p.pos.y / TEXTURE_SIZE)][(int)(p.pos.x / TEXTURE_SIZE)] != '1')
	{
		p.pos.x += cub->fov.dir.x;
		p.pos.y += cub->fov.dir.y;
		mlx_pixel_put(cub->mlx, cub->win, p.pos.x, p.pos.y, PINK);
	}
}

void	put_horizontal_line(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->win_width)
	{
		mlx_pixel_put(cub->mlx, cub->win, i, (cub->win_height / 2), GREEN);
		i++;
	}
}*/