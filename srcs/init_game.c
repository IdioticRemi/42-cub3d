/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/04/07 18:56:40 by seoyounglee      ###   ########lyon.fr   */
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
	// cub->player.x = cub->player.x_start * TILE_SIZE; // + (TILE_SIZE / 2);
	// cub->player.y = cub->player.y_start * TILE_SIZE; //+ (TILE_SIZE / 2);
	cub->player.pos_x = cub->player.x_start * (cub->win_width / cub->map.column_count);
	cub->player.pos_y = cub->player.y_start * (cub->win_height / cub->map.row_count);
	
	/* temp init -- to be changed according to conditions*/

	cub->player.dir_x = -1.0;
	cub->player.dir_y = 0.0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0.66;
	cub->player.move_speed = 0.05;
	cub->player.rotate_speed = 0.05;


	/***********************/

	
	printf("win_width: %d | win_height: %d\n", cub->win_width, cub->win_height);
	printf("colum: %d | row: %d\n", cub->map.column_count, cub->map.row_count);
	printf("startX: %f | startY: %f\n", cub->player.x_start, cub->player.y_start);
	printf("posX: %f | posY: %f\n", cub->player.pos_x, cub->player.pos_y);
	printf("x: %f | y: %f\n", cub->player.x, cub->player.y);
}

void	init_game(t_cub *cub)
{
	init_mlx_and_win(cub);
	init_player_value(cub);
}
