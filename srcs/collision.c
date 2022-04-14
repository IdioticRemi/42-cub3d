/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:49 by selee             #+#    #+#             */
/*   Updated: 2022/04/15 00:59:30 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	player_touched_wall(t_cub *cub, int direction)
{
	int		i;
	int		j;

	i = cub->player.pos_y;
	j = cub->player.pos_x;

	return ((direction == DIR_NO && cub->map.array[i - 1][j] == '1')
		|| (direction == DIR_SO && cub->map.array[i + 1][j] == '1')
		|| (direction == DIR_WE && cub->map.array[i][j - 1] == '1')
		|| (direction == DIR_EA && cub->map.array[i][j + 1] == '1'));
}
