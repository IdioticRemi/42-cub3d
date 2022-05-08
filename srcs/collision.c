/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:26 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 15:30:02 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vect	collision_handler(t_cub *cub)
{
	t_vect	direction;
	t_vect	final_pos;
	char	wall;

	direction = set_vector(cub->cam.yaw + FOV / 2, cub->cam.yaw + FOV / 2);
	if (cub->keys.key_w)
		direction = vector_add(direction, set_vector(0, 0));
	else if (cub->keys.key_s)
		direction = vector_add(direction, set_vector(PI, PI));
	else if (cub->keys.key_a)
		direction = vector_subs(direction, set_vector(PI / 2, PI / 2));
	else if (cub->keys.key_d)
		direction = vector_add(direction, set_vector(PI / 2, PI / 2));
	direction = set_vector(cos(direction.x), sin(direction.y));
	direction = vector_multi(direction, MOVE_SPEED);
	final_pos = vector_add(cub->player.pos, direction);
	wall = cub->map.array[(int)(final_pos.x / TILE_SIZE)]
	[(int)(cub->player.pos.y / TILE_SIZE)];
	if (wall == '1')
		direction.x = 0;
	wall = cub->map.array[(int)(cub->player.pos.x / TILE_SIZE)]
	[(int)(final_pos.y / TILE_SIZE)];
	if (wall == '1')
		direction.y = 0;
	return (direction);
}
