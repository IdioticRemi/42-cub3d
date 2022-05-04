/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:50 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 13:11:49 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_img_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dest;
	t_image	screen;

	screen = cub->screen;
	dest = screen.addr + (y * screen.line_length + x
			* (screen.bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	draw_background(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			mlx_img_pixel_put(cub, x, y, cub->info.ceiling);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
			mlx_img_pixel_put(cub, x, y, cub->info.floor);
		y++;
	}
}
