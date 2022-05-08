/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:27 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 15:31:34 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint64_t	ft_get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

t_rgba	mlx_img_pixel_get(t_image *img, int x, int y)
{
	char	*dest;
	t_rgba	color;

	dest = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	color.value = *(unsigned int *)dest;
	return (color);
}

void	precalc_img(t_image *img, t_rgba tab[64][64])
{
	int	x;
	int	y;

	x = -1;
	while (++x < 64)
	{
		y = -1;
		while (++y < 64)
		{
			tab[x][y] = mlx_img_pixel_get(img, x, y);
		}
	}
}

void	precalc_all(t_cub *cub)
{
	precalc_img(&cub->texture.north, cub->texture.n);
	precalc_img(&cub->texture.south, cub->texture.s);
	precalc_img(&cub->texture.east, cub->texture.e);
	precalc_img(&cub->texture.west, cub->texture.w);
	mlx_destroy_image(cub->mlx, cub->texture.north.ptr);
	mlx_destroy_image(cub->mlx, cub->texture.south.ptr);
	mlx_destroy_image(cub->mlx, cub->texture.east.ptr);
	mlx_destroy_image(cub->mlx, cub->texture.west.ptr);
}
