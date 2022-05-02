/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/05/02 11:45:29 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_img(t_cub *cub) /* temporary; to be modified later */
{
	cub->texture.wall.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/white_square32.xpm", &(cub->texture.wall.width),
			&(cub->texture.wall.height));
	cub->texture.space.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/black_square32.xpm", &(cub->texture.space.width),
			&(cub->texture.space.height));
}



