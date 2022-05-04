/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:41:09 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 17:43:13 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_horizontal(t_cub *cub, t_dda *dda, float angle, int max_dist)
{
	if (angle < PI)
	{
		dda->hori.x = cub->player.pos.x
			+ ((TILE_SIZE - dda->rel_pos.y) / tan(angle));
		dda->hori.y = cub->player.pos.y + TILE_SIZE - dda->rel_pos.y + 0.0001;
		dda->offset = set_vector(TILE_SIZE / tan(angle), TILE_SIZE);
	}
	if (angle > PI)
	{
		dda->hori.x = cub->player.pos.x - (dda->rel_pos.y / tan(angle));
		dda->hori.y = cub->player.pos.y - dda->rel_pos.y - 0.0001;
		dda->offset = set_vector(-TILE_SIZE / tan(angle), -TILE_SIZE);
	}
	if (angle == 0 || angle == PI)
	{
		dda->dist_hori = 99999 * TILE_SIZE;
		dda->dist = max_dist;
		dda->hori = cub->player.pos;
	}
}

void	calc_vertical(t_cub *cub, t_dda *dda, float angle, int max_dist)
{
	if (angle < PI / 2 || angle > PI / 2 * 3)
	{
		dda->vert.x = cub->player.pos.x + TILE_SIZE - dda->rel_pos.x + 0.0001;
		dda->vert.y = cub->player.pos.y
			+ ((TILE_SIZE - dda->rel_pos.x) * tan(angle));
		dda->offset = set_vector(TILE_SIZE, TILE_SIZE * tan(angle));
	}
	if (angle > PI / 2 && angle < PI / 2 * 3)
	{
		dda->vert.x = cub->player.pos.x - dda->rel_pos.x - 0.0001;
		dda->vert.y = cub->player.pos.y - dda->rel_pos.x * tan(angle);
		dda->offset = set_vector(-(TILE_SIZE), -TILE_SIZE * tan(angle));
	}
	if (angle == PI / 2 || angle == PI / 2 * 3)
	{
		dda->dist_vert = 99999 * TILE_SIZE;
		dda->dist = max_dist;
		dda->vert = cub->player.pos;
	}
}
