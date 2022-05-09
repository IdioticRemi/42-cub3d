/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:27 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 15:31:34 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_side	get_side_hit(t_dda dda)
{
	if (dda.dist_hori > dda.dist_vert)
	{
		if (dda.offset.x > 0)
			return (E);
		else
			return (W);
	}
	else
	{
		if (dda.offset.y < 0)
			return (N);
		else
			return (S);
	}
}

double	get_img_x(t_dda dda)
{
	t_side	side;

	side = get_side_hit(dda);
	if (side == E)
		return (fmod(dda.vert.y, TILE_SIZE));
	else if (side == W)
		return (TILE_SIZE - fmod(dda.vert.y, TILE_SIZE));
	else if (side == N)
		return (fmod(dda.hori.x, TILE_SIZE));
	else
		return (TILE_SIZE - fmod(dda.hori.x, TILE_SIZE));
}

void	cast_ray(t_cub *cub, double angle, int ray_id)
{
	static int	max_dist = 100;
	t_dda		dda;

	angle = fmod(angle, 2 * PI);
	dda.rel_pos.y = fmod(cub->player.pos.y, TILE_SIZE);
	dda.rel_pos.x = fmod(cub->player.pos.x, TILE_SIZE);
	dda.dist = 0;
	calc_horizontal(cub, &dda, angle, max_dist);
	get_horizontal_dist(cub, &dda, max_dist);
	dda.dist = 0;
	calc_vertical(cub, &dda, angle, max_dist);
	get_vertical_dist(cub, &dda, max_dist);
	angle = cos(ray_id * FOV_SHIFT - FOV / 2);
	dda.dist_final = fmin(dda.dist_hori, dda.dist_vert) * angle;
	draw_strip(cub, ray_id, dda);
}

void	raycaster(t_cub *cub)
{
	t_vect	mini_player;
	double	delta_cam;
	int		i;

	handle_movement(cub);
	i = -1;
	while (++i != STRIP_COUNT)
	{
		delta_cam = (double)i * FOV_SHIFT;
		cast_ray(cub, cub->cam.yaw + delta_cam, i);
	}
	render_minimap(cub);
	mini_player = vector_multi(cub->player.pos, MINIMAP_SCALE);
	bresenham(cub, mini_player, vector_add(mini_player,
			set_vector(cos(cub->cam.yaw) * 20,
				sin(cub->cam.yaw) * 20)), RED);
	bresenham(cub, mini_player, vector_add(mini_player,
			set_vector(cos(cub->cam.yaw + FOV) * 20,
				sin(cub->cam.yaw + FOV) * 20)), RED);
	put_point(cub, mini_player, RED);
}
