/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:27 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 16:35:17 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	math_map(float x, t_vect src_range, t_vect dst_range)
{
	float	out;

	if (x > src_range.y)
		return (dst_range.y);
	else if (x < src_range.x)
		return (dst_range.x);
	out = src_range.x + ((dst_range.y - dst_range.x)
			/ (src_range.y - src_range.x)) * (x - src_range.x);
	return (out);
}

float	math_dist(t_vect origin, t_vect arrival)
{
	float	dist;

	dist = sqrtf((arrival.x - origin.x) * (arrival.x - origin.x)
			+ (arrival.y - origin.y) * (arrival.y - origin.y));
	return (dist);
}

void	bresenham(t_cub *cub, t_vect src, t_vect dest, int color)
{
	double	step_x;
	double	step_y;
	int		i;

	step_x = dest.x - src.x;
	step_y = dest.y - src.y;
	i = fmax(fabs(step_x), fabs(step_y));
	step_x /= i;
	step_y /= i;
	while ((int)(src.x - dest.x) || (int)(src.y - dest.y))
	{
		if (!(src.x >= SCREEN_WIDTH || src.y >= SCREEN_HEIGHT
				|| src.x < 0 || src.y < 0))
			mlx_img_pixel_put(cub, src.x, src.y, color);
		src.x += step_x;
		src.y += step_y;
	}
}

void	cast_ray(t_cub *cub, float angle, int rayID)
{
	static int	max_dist = 8;
	int			dist;
	float		dist_vert;
	float		dist_hori;
	float		dist_final;
	t_dda		dda;

	while (angle > 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	dda.rel_pos.y = cub->player.pos.y;
	while (dda.rel_pos.y > TILE_SIZE)
		dda.rel_pos.y -= TILE_SIZE;
	dda.rel_pos.x = cub->player.pos.x;
	while (dda.rel_pos.x > TILE_SIZE)
		dda.rel_pos.x -= TILE_SIZE;
	// HORIZONTAL
	dist = 0;
	if (angle < PI)
	{
		dda.hori.y = cub->player.pos.y + TILE_SIZE - dda.rel_pos.y + 0.0001;
		dda.hori.x = cub->player.pos.x + ((TILE_SIZE - dda.rel_pos.y) / tan(angle));
		dda.offset = set_vector(TILE_SIZE / tan(angle), TILE_SIZE);
	}
	if (angle > PI)
	{
		dda.hori.y = cub->player.pos.y - dda.rel_pos.y - 0.0001;
		dda.hori.x = cub->player.pos.x - (dda.rel_pos.y / tan(angle));
		dda.offset = set_vector(-TILE_SIZE / tan(angle), -TILE_SIZE);
	}
	if (angle == 0 || angle == PI)
	{
		dist_hori = 99999 * TILE_SIZE;
		dist = max_dist;
		dda.hori = cub->player.pos;
	}
	while (dist < max_dist)
	{
		dda.map_x = dda.hori.x / TILE_SIZE;
		dda.map_y = dda.hori.y / TILE_SIZE;
		if (dda.map_x >= 0 && dda.map_y >= 0 && dda.map_x < cub->map.column_count && dda.map_y < cub->map.row_count && cub->map.array[dda.map_x][dda.map_y] == '1')
			dist = max_dist;
		else
			dda.hori = vector_add(dda.hori, dda.offset);
		dist++;
	}
	dist_hori = math_dist(cub->player.pos, dda.hori);
	// VERTICAL
	dist = 0;
	if (angle < PI / 2 || angle > PI / 2 * 3)
	{
		// RIGHT
		dda.vert.y = cub->player.pos.y + ((TILE_SIZE - dda.rel_pos.x) * tan(angle));
		dda.vert.x = cub->player.pos.x + TILE_SIZE - dda.rel_pos.x + 0.0001;
		dda.offset = set_vector(TILE_SIZE, TILE_SIZE * tan(angle));
	}
	if (angle > PI / 2 && angle < PI / 2 * 3)
	{
		// LEFT
		dda.vert.y = cub->player.pos.y - dda.rel_pos.x * tan(angle);
		dda.vert.x = cub->player.pos.x - dda.rel_pos.x - 0.0001;
		dda.offset = set_vector(-(TILE_SIZE), -TILE_SIZE * tan(angle));
	}
	if (angle == PI / 2 || angle == PI / 2 * 3)
	{
		dist_vert = 99999 * TILE_SIZE;
		dist = max_dist;
		dda.vert = cub->player.pos;
	}
	while (dist < max_dist)
	{
		dda.map_x = dda.vert.x / TILE_SIZE;
		dda.map_y = dda.vert.y / TILE_SIZE;
		if (dda.map_x >= 0 && dda.map_y >= 0 && dda.map_x < cub->map.column_count && dda.map_y < cub->map.row_count && cub->map.array[dda.map_x][dda.map_y] == '1')
			dist = max_dist;
		else
			dda.vert = vector_add(dda.vert, dda.offset);
		dist_vert = math_dist(cub->player.pos, dda.vert);
		if (dist_vert > dist_hori)
			dist = max_dist;
		dist++;
	}
	// 2D!
	// if (dist_hori > dist_vert)
	// 	bresenham(cub, cub->player.pos, dda.vert, RED);
	// else
	// 	bresenham(cub, cub->player.pos, dda.hori, RED);
	// 3D!
	angle = cos(angle - cub->cam.yaw - FOV / 2);
	// if (rayID == 0 || rayID - STRIP_COUNT == -1 || rayID == STRIP_COUNT / 2)
	// 	dprintf(1, "%3d > %f\n", rayID, angle);
	dist_final = fmin(dist_hori, dist_vert) * angle;
	draw_strip(cub, rayID, dist_final, dist_hori < dist_vert);
}

void	raycaster(t_cub *cub)
{
	t_vect	mini_player;
	float	delta_cam;
	t_vect	src_range;
	t_vect	dst_range;
	int		i;

	handle_movement(cub);
	src_range = set_vector(0, STRIP_COUNT);
	dst_range = set_vector(-FOV / 2, FOV / 2);
	i = -1;
	while (++i != STRIP_COUNT)
	{
		delta_cam = math_map(i, src_range, dst_range);
		cast_ray(cub, cub->cam.yaw + delta_cam, i);
	}
	render_minimap(cub);
	mini_player = vector_multi(cub->player.pos, MINIMAP_SCALE);
	bresenham(cub, mini_player, vector_add(mini_player,
			set_vector(cos(cub->cam.yaw - FOV / 2) * 20,
				sin(cub->cam.yaw - FOV / 2) * 20)), PINK);
	bresenham(cub, mini_player, vector_add(mini_player,
			set_vector(cos(cub->cam.yaw + FOV / 2) * 20,
				sin(cub->cam.yaw + FOV / 2) * 20)), PINK);
	put_point(cub, mini_player, BLACK);
}
