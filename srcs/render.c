/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:50 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 16:36:57 by selee            ###   ########lyon.fr   */
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

void	put_point(t_cub *cub, t_vect crd, int color)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 5)
	{
		y = -1;
		while (++y < 5)
		{
			if (!(crd.x + x - 2 < 0
					|| crd.x + x - 2 > SCREEN_WIDTH
					|| crd.y + y - 2 < 0
					|| crd.y + y - 2 > SCREEN_HEIGHT))
				mlx_img_pixel_put(cub, crd.x + x - 2, crd.y + y - 2, color);
		}
	}
}

void	draw_strip(t_cub *cub, int rayID, float dist, int side)
{
	int		len;
	float	d;
	int		x;
	int		y;
	t_rgba	color;

	color.value = WHITE;
	d = (dist / TILE_SIZE) - 0.42;
	if (d >= 1)
	{
		color.r *= 1.0 / d;
		color.g *= 1.0 / d;
		color.b *= 1.0 / d;
	}
	color.r = math_map(color.r, set_vector(0, 255), set_vector(80, 200));
	color.g = math_map(color.g, set_vector(0, 255), set_vector(80, 200));
	color.b = math_map(color.b, set_vector(0, 255), set_vector(80, 200));
	if (side)
	{
		color.r *= 0.8;
		color.g *= 0.8;
		color.b *= 0.8;
	}
	len = SCREEN_HEIGHT / (dist / TILE_SIZE);
	if (len < 50)
		len = 50;
	if (len > SCREEN_HEIGHT)
		len = SCREEN_HEIGHT;
	x = -1;
	while (++x < STRIP_WIDTH)
	{
		y = -1;
		while (++y < len)
		{
			mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
				SCREEN_HEIGHT / 2 - len / 2 + y, color.value);
		}
	}
}
