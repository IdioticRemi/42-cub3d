/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/04/05 16:59:08 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_value(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map.row_count = 0;
	cub->map.column_count = 0;
}

void	init_mlx_and_win(t_cub *cub)
{
	cub->win_width = cub->map.column_count * TILE_SIZE;
	cub->win_height = cub->map.row_count * TILE_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
}
void	init_player_value(t_cub *cub) //グリッドの真ん中に見えるように
{
	cub->player.x = cub->player.x_start * TILE_SIZE  + (TILE_SIZE / 2);
	cub->player.y = cub->player.y_start * TILE_SIZE + (TILE_SIZE / 2);
	
}

void	init_game(t_cub *cub)
{
	init_player_value(cub);
	init_mlx_and_win(cub);
}
