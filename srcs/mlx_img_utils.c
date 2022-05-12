/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_img_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:42:16 by tjolivea          #+#    #+#             */
/*   Updated: 2022/05/09 13:42:17 by tjolivea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_img_pixel_put(t_cub *cub, int x, int y, unsigned int color)
{
	char	*dest;
	t_image	screen;

	if (x < 0 || y < 0 || x > SCREEN_WIDTH || y > SCREEN_HEIGHT)
		return ;
	screen = cub->screen;
	dest = screen.addr + (y * screen.ln + x
			* (screen.bpp / 8));
	*(unsigned int *)dest = color;
}

t_rgba	mlx_img_pixel_get(t_image *img, int x, int y)
{
	char	*dest;
	t_rgba	color;

	dest = img->addr + (y * img->ln + x
			* (img->bpp / 8));
	color.value = *(unsigned int *)dest;
	return (color);
}

void	init_mlx(t_cub *cub)
{
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	cub->screen.ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->screen.addr = mlx_get_data_addr(cub->screen.ptr,
			&cub->screen.bpp,
			&cub->screen.ln, &cub->screen.e);
}
