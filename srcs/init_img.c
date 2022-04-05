/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:19 by selee             #+#    #+#             */
/*   Updated: 2022/04/05 17:08:44 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_img(t_cub *cub)
{
	cub->player.image.ptr = mlx_xpm_file_to_image(cub->mlx, "./assets_xpm/player_test.xpm", &(cub->player.image.width), &(cub->player.image.height)); 
}

void	init_tile_img(t_cub *cub)
{
	cub->tile.wall.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/yellow_square32.xpm", &(cub->tile.wall.width),
			&(cub->tile.wall.height));
	cub->tile.space.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/black_square32.xpm", &(cub->tile.space.width),
			&(cub->tile.space.height));
}

void	init_game_img(t_cub *cub)
{
	init_player_img(cub);
	init_tile_img(cub);
}
