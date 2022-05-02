/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/05/02 10:52:10 by selee            ###   ########lyon.fr   */
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

void	init_mlx_and_win(t_cub *cub)
{
	cub->win_width = SCREEN_WIDTH;
	cub->win_height = SCREEN_HEIGHT;
	// cub->win_width = cub->map.column_count * TILE_SIZE;
	// cub->win_height = cub->map.row_count * TILE_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
}

void	init_game(t_cub *cub)
{
	init_struct_player(cub);
	init_struct_fov(cub);
	init_mlx_and_win(cub);
	// init_game_img(cub);
}
