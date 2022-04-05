/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:26 by selee             #+#    #+#             */
/*   Updated: 2022/04/05 18:02:02 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_north(t_cub *cub)
{
	cub->player.y--;
}

void	move_south(t_cub *cub)
{
	cub->player.y++;
}

void	move_west(t_cub *cub)
{
	cub->player.x--;
}

void	move_east(t_cub *cub)
{
	cub->player.x++;
}

void	move_to_directions(t_cub *cub, int direction)
{
	// if (!player_touched_wall(cub, direction))
	// {
		if (direction == DIR_NO)
			move_north(cub);
		else if (direction == DIR_SO)
			move_south(cub);
		else if (direction == DIR_WE)
			move_west(cub);
		else if (direction == DIR_EA)
			move_east(cub);
	// }
}
