/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:26 by selee             #+#    #+#             */
/*   Updated: 2022/04/05 17:10:45 by selee            ###   ########lyon.fr   */
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

/****** temp functions *********
void	move_north(t_cub *cub)
{
	int	old_x = cub->player.x;
	int	old_y = cub->player.y;

	if ((0 < cub->player.x && cub->player.x <= cub->win_width)
		&& (0 < cub->player.y && cub->player.y <= cub->win_height))
	{
		mlx_pixel_put(cub->mlx, cub->win, old_x, old_y, BLACK);
		mlx_pixel_put(cub->mlx, cub->win, cub->player.x, --cub->player.y, YELLOW);
	}
	// cub->player.y--;
}

void	move_south(t_cub *cub)
{
	int	old_x = cub->player.x;
	int	old_y = cub->player.y;

	if ((0 < cub->player.x && cub->player.x <= cub->win_width)
		&& (0 < cub->player.y && cub->player.y <= cub->win_height))
	{
		mlx_pixel_put(cub->mlx, cub->win, old_x, old_y, BLACK);
		mlx_pixel_put(cub->mlx, cub->win, cub->player.x, ++cub->player.y, YELLOW);
	}

	// cub->player.y++;
}

void	move_west(t_cub *cub)
{
	int	old_x = cub->player.x;
	int	old_y = cub->player.y;

	if ((0 < cub->player.x && cub->player.x <= cub->win_width)
		&& (0 < cub->player.y && cub->player.y <= cub->win_height))
	{
		mlx_pixel_put(cub->mlx, cub->win, old_x, old_y, BLACK);
		mlx_pixel_put(cub->mlx, cub->win, --cub->player.x, cub->player.y, YELLOW);
	}
	// cub->player.x--;
}

void	move_east(t_cub *cub)
{
	int	old_x = cub->player.x;
	int	old_y = cub->player.y;

	if ((0 < cub->player.x && cub->player.x <= cub->win_width)
		&& (0 < cub->player.y && cub->player.y <= cub->win_height))
	{
		mlx_pixel_put(cub->mlx, cub->win, old_x, old_y, BLACK);
		mlx_pixel_put(cub->mlx, cub->win, ++cub->player.x, cub->player.y, YELLOW);
	}
	// cub->player.x++;
}
****** temp functions **********/

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
