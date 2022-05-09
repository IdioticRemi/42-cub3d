/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:50 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:17:42 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgba	get_side_texture_pixel(t_cub *cub, t_dda dda, int x, int y)
{
	t_side	side;

	side = get_side_hit(dda);
	if (side == E)
		return (cub->tx.e[x][y]);
	else if (side == W)
		return (cub->tx.w[x][y]);
	else if (side == N)
		return (cub->tx.n[x][y]);
	else
		return (cub->tx.s[x][y]);
}

void	apply_depth(t_rgba *color, double dist)
{
	double	scale;

	if (dist >= 1)
	{
		scale = 1.0 / dist;
		color->r *= scale;
		color->g *= scale;
		color->b *= scale;
	}
}

void	draw_background(t_cub *cub, int len, int rayID)
{
	int	diff;
	int	x;
	int	y;

	if (len < SCREEN_HEIGHT)
	{
		diff = (SCREEN_HEIGHT - len) / 2 + 2;
		y = -1;
		while (++y < diff)
		{
			x = -1;
			while (++x < STRIP_WIDTH)
				mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
					y, cub->info.ceiling);
		}
		y = diff;
		while (--y > 0)
		{
			x = -1;
			while (++x < STRIP_WIDTH)
				mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
					SCREEN_HEIGHT - y, cub->info.floor);
		}
	}
}

void	strip_calc(t_cub *cub, t_dda dda, t_strip s, int rayID)
{
	int	x;
	int	y;

	if (SCREEN_HEIGHT < s.len)
		y = s.len / 2 - SCREEN_HEIGHT / 2 - 1;
	else
		y = -1;
	while (++y < s.len)
	{
		if (SCREEN_HEIGHT / 2 - s.len / 2 + y > SCREEN_HEIGHT)
			break ;
		if ((double)y / (double)s.len * 64.0 != s.before)
		{
			s.before = (double)y / (double)s.len * 64.0;
			s.color = get_side_texture_pixel(cub, dda, s.img_x, s.before);
			apply_depth(&s.color, s.d);
		}
		x = -1;
		while (++x < STRIP_WIDTH)
			mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
				SCREEN_HEIGHT / 2 - s.len / 2 + y, s.color.value);
	}
}

void	draw_strip(t_cub *cub, int rayID, t_dda dda)
{
	t_strip	s;

	s.d = (dda.dist_final / TILE_SIZE) - 0.1;
	s.len = fmax(SCREEN_HEIGHT / (dda.dist_final / TILE_SIZE), 50);
	s.img_x = get_img_x(dda) / TILE_SIZE * 64.0;
	s.before = 0;
	s.color = get_side_texture_pixel(cub, dda, s.img_x, s.before);
	apply_depth(&s.color, s.d);
	draw_background(cub, s.len, rayID);
	strip_calc(cub, dda, s, rayID);
}
