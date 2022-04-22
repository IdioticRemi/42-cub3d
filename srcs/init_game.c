/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:46 by selee             #+#    #+#             */
/*   Updated: 2022/04/22 18:14:40 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_and_win(t_cub *cub)
{
	cub->win_width = SCREEN_WIDTH;
	cub->win_height = SCREEN_HEIGHT;
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, cub->win_width, cub->win_height, "cub3d");
}

void	init_game(t_cub *cub)
{
	init_struct_player(cub);
	init_struct_fov(cub);
	init_mlx_and_win(cub);
}
