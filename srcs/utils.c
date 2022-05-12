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

static void	precalc_img(t_image *img, t_rgba tab[64][64])
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
	precalc_img(&cub->tx.north, cub->tx.n);
	precalc_img(&cub->tx.south, cub->tx.s);
	precalc_img(&cub->tx.east, cub->tx.e);
	precalc_img(&cub->tx.west, cub->tx.w);
	mlx_destroy_image(cub->mlx, cub->tx.north.ptr);
	mlx_destroy_image(cub->mlx, cub->tx.south.ptr);
	mlx_destroy_image(cub->mlx, cub->tx.east.ptr);
	mlx_destroy_image(cub->mlx, cub->tx.west.ptr);
}
