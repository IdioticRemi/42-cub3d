/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:10 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 16:19:12 by selee            ###   ########lyon.fr   */
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
			if (cub->map.array[i][j] == 'P')
			{
				cub->player.x_start = j;
				cub->player.y_start = i;
				cub->player.x = j;
				cub->player.y = i;
			}
			j++;
		}
		i++;
	}
}
