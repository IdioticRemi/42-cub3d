/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:48:27 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 17:41:49 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_horizontal_dist(t_cub *cub, t_dda *dda, int max_dist)
{
	while (dda->dist < max_dist)
	{
		dda->map_x = dda->hori.x / TILE_SIZE;
		dda->map_y = dda->hori.y / TILE_SIZE;
		if (dda->map_x >= 0 && dda->map_y >= 0
			&& dda->map_x < cub->map.column_count
			&& dda->map_y < cub->map.row_count
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
			&& dda->map_x < cub->map.column_count
			&& dda->map_y < cub->map.row_count
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

void	cast_ray(t_cub *cub, float angle, int ray_id)
{
	static int	max_dist = 8;
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
	dda.dist = 0;
	calc_horizontal(cub, &dda, angle, max_dist);
	get_horizontal_dist(cub, &dda, max_dist);
	dda.dist = 0;
	calc_vertical(cub, &dda, angle, max_dist);
	get_vertical_dist(cub, &dda, max_dist);
	angle = cos(angle - cub->cam.yaw - FOV / 2);
	dda.dist_final = fmin(dda.dist_hori, dda.dist_vert) * angle;
	draw_strip(cub, ray_id, dda.dist_final, dda.dist_hori < dda.dist_vert);
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

/*
void	cast_ray(t_cub *cub, float angle, int ray_id)
{
	static int	max_dist = 8;
	t_dda		dda;
	int			dist;
	float		dist_vert;
	float		dist_hori;
	float		dist_final;

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
	// if (ray_id == 0 || ray_id - STRIP_COUNT == -1 || ray_id == STRIP_COUNT / 2)
	// 	dprintf(1, "%3d > %f\n", ray_id, angle);
	dist_final = fmin(dist_hori, dist_vert) * angle;
	draw_strip(cub, ray_id, dist_final, dist_hori < dist_vert);
}*/