/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:26 by selee             #+#    #+#             */
/*   Updated: 2022/04/12 19:50:19 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*

◦ The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through
the maze.

*/

void	move_north(t_cub *cub)
{
	cub->player.pos_y--;
}

void	move_south(t_cub *cub)
{
	cub->player.pos_y++;
}

void	move_west(t_cub *cub)
{
	cub->player.pos_x--;
}

void	move_east(t_cub *cub)
{
	cub->player.pos_x++;
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
