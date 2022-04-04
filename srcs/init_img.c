/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:39:31 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 15:00:08 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tile_img(t_cub *cub)
{
	cub->tile.wall.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/yellow_square32.xpm", &(cub->tile.wall.width),
			&(cub->tile.wall.height));
	cub->tile.space.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/blakc_square32.xpm", &(cub->tile.space.width),
			&(cub->tile.space.height));
	// cub->tile.exit.ptr = mlx_xpm_file_to_image(cub->mlx,
	// 		"./assets_xpm/house32.xpm", &(cub->tile.exit.width),
	// 		&(cub->tile.exit.height));
}

void	init_game_img(t_cub *cub)
{
	init_tile_img(cub);
}
