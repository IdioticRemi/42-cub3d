/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:10 by selee             #+#    #+#             */
/*   Updated: 2022/04/15 22:32:16 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_get_coord(t_cub *cub)
{	
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.row_count)
	{
		j = 0;
		while (j < cub->map.column_count)
		{
			if (cub->map.array[i][j] == 'N'
				||cub->map.array[i][j] == 'S'
				||cub->map.array[i][j] == 'W'
				||cub->map.array[i][j] == 'E')
			{
				cub->map.start_dir = cub->map.array[i][j];
				cub->player.start_pos = set_vector(j, i);
				// cub->player.x_start = j;
				// cub->player.y_start = i;
			}
			j++;
		}
		i++;
	}
}
