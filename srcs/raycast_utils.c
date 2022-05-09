/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:41:09 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 15:23:02 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_horizontal(t_cub *cub, t_dda *dda, double angle, int max_dist)
{
	if (angle < PI)
	{
		dda->hori.x = cub->player.pos.x
			+ ((TILE_SIZE - dda->rel_pos.y) / tan(angle));
		dda->hori.y = cub->player.pos.y + TILE_SIZE - dda->rel_pos.y + 0.001;
		dda->offset = set_vector(TILE_SIZE / tan(angle), TILE_SIZE);
	}
	if (angle > PI)
	{
		dda->hori.x = cub->player.pos.x - (dda->rel_pos.y / tan(angle));
		dda->hori.y = cub->player.pos.y - dda->rel_pos.y - 0.001;
		dda->offset = set_vector(-TILE_SIZE / tan(angle), -TILE_SIZE);
	}
	if (angle == 0 || angle == PI)
	{
		dda->dist_hori = 99999 * TILE_SIZE;
		dda->dist = max_dist;
		dda->hori = cub->player.pos;
	}
}

void	calc_vertical(t_cub *cub, t_dda *dda, double angle, int max_dist)
{
	if (angle < PI / 2 || angle > PI / 2 * 3)
	{
		dda->vert.x = cub->player.pos.x + TILE_SIZE - dda->rel_pos.x + 0.001;
		dda->vert.y = cub->player.pos.y
			+ ((TILE_SIZE - dda->rel_pos.x) * tan(angle));
		dda->offset = set_vector(TILE_SIZE, TILE_SIZE * tan(angle));
	}
	if (angle > PI / 2 && angle < PI / 2 * 3)
	{
		dda->vert.x = cub->player.pos.x - dda->rel_pos.x - 0.001;
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

void	get_horizontal_dist(t_cub *cub, t_dda *dda, int max_dist)
{
	while (dda->dist < max_dist)
	{
		dda->map_x = dda->hori.x / TILE_SIZE;
		dda->map_y = dda->hori.y / TILE_SIZE;
		if (dda->map_x >= 0 && dda->map_y >= 0
			&& dda->map_x < cub->map.w
			&& dda->map_y < cub->map.h
			&& cub->map.array[dda->map_x][dda->map_y] == '1')
			dda->dist = max_dist;
		else
			dda->hori = vector_add(dda->hori, dda->offset);
		dda->dist++;
	}
	dda->dist_hori = math_dist(cub->player.pos, dda->hori);
}

void	get_vertical_dist(t_cub *cub, t_dda *dda, int max_dist)
{
	while (dda->dist < max_dist)
	{
		dda->map_x = dda->vert.x / TILE_SIZE;
		dda->map_y = dda->vert.y / TILE_SIZE;
		if (dda->map_x >= 0 && dda->map_y >= 0
			&& dda->map_x < cub->map.w
			&& dda->map_y < cub->map.h
			&& cub->map.array[dda->map_x][dda->map_y] == '1')
			dda->dist = max_dist;
		else
			dda->vert = vector_add(dda->vert, dda->offset);
		dda->dist_vert = math_dist(cub->player.pos, dda->vert);
		if (dda->dist_vert > dda->dist_hori)
			dda->dist = max_dist;
		dda->dist++;
	}
}
