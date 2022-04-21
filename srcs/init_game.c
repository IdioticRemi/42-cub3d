/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/04/21 14:18:20 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_img(t_cub *cub) /* temporary; to be modified later */
{
	cub->tile.wall.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/white_square32.xpm", &(cub->tile.wall.width),
			&(cub->tile.wall.height));
	cub->tile.space.ptr = mlx_xpm_file_to_image(cub->mlx,
			"./assets_xpm/black_square32.xpm", &(cub->tile.space.width),
			&(cub->tile.space.height));
}

void	init_mlx_and_win(t_cub *cub)
{
	cub->win_width = 640;// (cub->map.column_count * GRID_SIZE);
	cub->win_height = 480;//cub->map.row_count * GRID_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
}

void	init_game(t_cub *cub)
{
	init_struct_player(cub);
	init_struct_fov(cub);
	init_mlx_and_win(cub);
	init_game_img(cub);
}
