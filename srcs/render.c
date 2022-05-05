/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:50 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 15:26:48 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_img_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dest;
	t_image	screen;

	if (x > SCREEN_WIDTH || x < 0 || y > SCREEN_HEIGHT || y < 0)
		return ;
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

t_rgba	get_side_texture_pixel(t_cub *cub, t_dda dda, int x, int y)
{
	t_side	side;

	side = get_side_hit(dda);
	if (side == E)
		return (cub->texture.e[x][y]);
	else if (side == W)
		return (cub->texture.w[x][y]);
	else if (side == N)
		return (cub->texture.n[x][y]);
	else
		return (cub->texture.s[x][y]);
}

void	apply_depth(t_rgba *color, float dist)
{
	float scale;

	if (dist >= 1)
	{
		scale = 1.0 / dist;
		color->r *= scale;
		color->g *= scale;
		color->b *= scale;
	}
}

void	draw_strip(t_cub *cub, int rayID, t_dda dda)
{
	int		len;
	float	d;
	int		x;
	int		y;
	int		imgX;
	int		before;
	t_rgba	color;

	d = (dda.dist_final / TILE_SIZE) - 0.1;
	len = fmax(SCREEN_HEIGHT / (dda.dist_final / TILE_SIZE), 50);
	imgX = get_img_x(dda) / TILE_SIZE * 64.0;
	before = 0;
	color = get_side_texture_pixel(cub, dda, imgX, before);
	apply_depth(&color, d);
	y = -1;
	while (++y < len)
	{
		if (SCREEN_HEIGHT / 2 - len / 2 + y < 0)
			y = len / 2 - SCREEN_HEIGHT / 2 - 1;
		if (SCREEN_HEIGHT / 2 - len / 2 + y > SCREEN_HEIGHT)
			break ;
		if ((float)y / (float)len * 64.0 != before)
		{
			before = (float)y / (float)len * 64.0;
			color = get_side_texture_pixel(cub, dda, imgX, before);
			apply_depth(&color, d);
		}
		x = -1;
		while (++x < STRIP_WIDTH)
		{
			mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
				SCREEN_HEIGHT / 2 - len / 2 + y, color.value);
		}
	}
}
