/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/04/15 23:02:54 by seoyounglee      ###   ########lyon.fr   */
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
	cub->win_width = (cub->map.column_count * TILE_SIZE) * 2;
	cub->win_height = cub->map.row_count * TILE_SIZE;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
}

void	init_player_direction(t_cub *cub)
{
	if (cub->map.start_dir == 'N')
		cub->fov.dir.y = -1;
	else if (cub->map.start_dir == 'S')
		cub->fov.dir.y = 1;
	else if (cub->map.start_dir == 'W')
		cub->fov.dir.x = -1;
	else if (cub->map.start_dir == 'E')
		cub->fov.dir.x = 1;	
}

void	init_player_value(t_cub *cub) //グリッドの真ん中に見えるように
{
	// cub->player.x = cub->player.start_pos.x * TILE_SIZE; // + (TILE_SIZE / 2);
	// cub->player.y = cub->player.y_start * TILE_SIZE; //+ (TILE_SIZE / 2);
	cub->player.pos = set_vector(cub->player.start_pos.x * TILE_SIZE, cub->player.start_pos.y * TILE_SIZE);

	/* temp init -- to be changed according to conditions*/
	cub->fov.dir = set_vector(0.0, 0.0);
	init_player_direction(cub);

	cub->fov.plane = set_vector(0.0, 0.66);
	cub->fov.move_speed = 0.05;
	cub->fov.rot_angle = 0.05;
	/***********************/

	printf("win_width: %d | win_height: %d\n", cub->win_width, cub->win_height);
	printf("colum: %d | row: %d\n", cub->map.column_count, cub->map.row_count);
	printf("startX: %f | startY: %f\n", cub->player.start_pos.x, cub->player.start_pos.y);
	printf("posX: %f | posY: %f\n", cub->player.pos.x, cub->player.pos.y);
}

void	init_game(t_cub *cub)
{
	init_mlx_and_win(cub);
	init_player_value(cub);
}
