#include "cub3d.h"

float	math_map(float x, t_vect src_range, t_vect dst_range)
{
	float out;

	if (x > src_range.y)
		return (dst_range.y);
	else if (x < src_range.x)
		return (dst_range.x);
	out = src_range.x + ((dst_range.y - dst_range.x) / (src_range.y - src_range.x)) * (x - src_range.x);

	return (out);
}

float	math_dist(t_vect origin, t_vect arrival)
{
	float dist;

	dist = sqrtf((arrival.x - origin.x) * (arrival.x - origin.x) + (arrival.y - origin.y) * (arrival.y - origin.y));
	return (dist);
}


void	put_point(t_cub *cub, t_vect coords, int color)
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (!(coords.x + x - 2 < 0 || coords.x + x - 2 > SCREEN_WIDTH || coords.y + y - 2 < 0 || coords.y + y - 2 > SCREEN_HEIGHT))
				mlx_img_pixel_put(cub, coords.x + x - 2, coords.y + y - 2, color);
		}
	}
}

void	draw_strip(t_cub *cub, int rayID, float dist)
{
	int		len;
	float	d;
	int		x;
	int		y;
	t_rgba	color;

	color.value = WHITE;
	d = (dist / TILE_SIZE) - 0.42;
	if (d >= 1)
	{
		color.r *= 1.0 / d;
		color.g *= 1.0 / d;
		color.b *= 1.0 / d;
	}
	color.r = math_map(color.r, set_vector(0, 255), set_vector(80, 200));
	color.g = math_map(color.g, set_vector(0, 255), set_vector(80, 200));
	color.b = math_map(color.b, set_vector(0, 255), set_vector(80, 200));
	len = SCREEN_HEIGHT / (dist / TILE_SIZE);
	if (len < 50)
		len = 50;
	if (len > SCREEN_HEIGHT)
		len = SCREEN_HEIGHT;
	x = -1;
	while (++x < STRIP_WIDTH)
	{
		y = -1;
		while (++y < len)
		{
			mlx_img_pixel_put(cub, rayID * STRIP_WIDTH + x,
				SCREEN_HEIGHT / 2 - len / 2 + y, color.value);
		}
	}
}

void	bresenham(t_cub *cub, t_vect src, t_vect dest, int color)
{
	double	stepX;
	double	stepY;
	int i;

	stepX = dest.x - src.x;
	stepY = dest.y - src.y;
	i = fmax(fabs(stepX), fabs(stepY));
	stepX /= i;
	stepY /= i;
	while ((int)(src.x - dest.x) || (int)(src.y - dest.y))
	{
		if (!(src.x >= SCREEN_WIDTH || src.y >= SCREEN_HEIGHT || src.x < 0 || src.y < 0))
			mlx_img_pixel_put(cub, src.x, src.y, color);
		src.x += stepX;
		src.y += stepY;
	}
}

void	render_map(t_cub *cub)
{
	for (int x = 0; x < cub->map.column_count; x++)
	{
		for (int y = 0; y < cub->map.row_count; y++)
		{
			int shiftX = x * TILE_SIZE;
			int shiftY = y * TILE_SIZE;
			char tile = cub->map.array[x][y];
			char obstacle = tile == '1';
			for (int a = 0; a < TILE_SIZE - 1; a++)
			{
				for (int b = 0; b < TILE_SIZE - 1; b++)
				{
					if (obstacle)
						mlx_img_pixel_put(cub, shiftX + a, shiftY + b, BLACK);
					else
						mlx_img_pixel_put(cub, shiftX + a, shiftY + b, WHITE);
				}
			}
		}
	}
}

void	cast_ray(t_cub *cub, float angle, int rayID)
{
	static int	max_dist = 8;
	int		dist;
	float	distVert;
	float	distHori;
	float	distFinal;
	t_dda	dda;

	while (angle > 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	dda.relPos.y = cub->player.pos.y;
	while (dda.relPos.y > TILE_SIZE)
		dda.relPos.y -= TILE_SIZE;
	dda.relPos.x = cub->player.pos.x;
	while (dda.relPos.x > TILE_SIZE)
		dda.relPos.x -= TILE_SIZE;

	// HORIZONTAL
	dist = 0;
	if (angle < PI)
	{
		dda.hori.y = cub->player.pos.y + TILE_SIZE - dda.relPos.y + 0.0001;
		dda.hori.x = cub->player.pos.x + ((TILE_SIZE - dda.relPos.y) / tan(angle));
		dda.offset = set_vector(TILE_SIZE / tan(angle), TILE_SIZE);
	}
	if (angle > PI)
	{
		dda.hori.y = cub->player.pos.y - dda.relPos.y - 0.0001;
		dda.hori.x = cub->player.pos.x - (dda.relPos.y / tan(angle));
		dda.offset = set_vector(-TILE_SIZE / tan(angle), -TILE_SIZE);
	}
	if (angle == 0 || angle == PI)
	{
		distHori = 99999 * TILE_SIZE;
		dist = max_dist;
		dda.hori = cub->player.pos;
	}
	while (dist < max_dist)
	{
		dda.mapX = dda.hori.x / TILE_SIZE;
		dda.mapY = dda.hori.y / TILE_SIZE;
		if (dda.mapX >= 0 && dda.mapY >= 0 && dda.mapX < cub->map.column_count && dda.mapY < cub->map.row_count && cub->map.array[dda.mapX][dda.mapY] == '1')
			dist = max_dist;
		else
			dda.hori = vector_add(dda.hori, dda.offset);
		dist++;
	}
	distHori = math_dist(cub->player.pos, dda.hori);

	// VERTICAL
	dist = 0;
	if (angle < PI / 2 || angle > PI / 2 * 3)
	{ // RIGHT
		dda.vert.y = cub->player.pos.y + ((TILE_SIZE - dda.relPos.x) * tan(angle));
		dda.vert.x = cub->player.pos.x + TILE_SIZE - dda.relPos.x + 0.0001;
		dda.offset = set_vector(TILE_SIZE, TILE_SIZE * tan(angle));
	}
	if (angle > PI / 2 && angle < PI / 2 * 3)
	{ // LEFT
		dda.vert.y = cub->player.pos.y - dda.relPos.x * tan(angle);
		dda.vert.x = cub->player.pos.x - dda.relPos.x - 0.0001;
		dda.offset = set_vector(-(TILE_SIZE), -TILE_SIZE * tan(angle));
	}
	if (angle == PI / 2 || angle == PI / 2 * 3)
	{
		distVert = 99999 * TILE_SIZE;
		dist = max_dist;
		dda.vert = cub->player.pos;
	}

	while (dist < max_dist)
	{
		dda.mapX = dda.vert.x / TILE_SIZE;
		dda.mapY = dda.vert.y / TILE_SIZE;
		if (dda.mapX >= 0 && dda.mapY >= 0 && dda.mapX < cub->map.column_count && dda.mapY < cub->map.row_count && cub->map.array[dda.mapX][dda.mapY] == '1')
			dist = max_dist;
		else
			dda.vert = vector_add(dda.vert, dda.offset);
		distVert = math_dist(cub->player.pos, dda.vert);
		if (distVert > distHori)
			dist = max_dist;
		dist++;
	}

	// 2D!
	// if (distHori > distVert)
	// 	bresenham(cub, cub->player.pos, dda.vert, RED);
	// else
	// 	bresenham(cub, cub->player.pos, dda.hori, RED);

	// 3D!
	angle = cos(angle - cub->cam.yaw - FOV / 2);
	
	
	// if (rayID == 0 || rayID - STRIP_COUNT == -1 || rayID == STRIP_COUNT / 2)
	// 	dprintf(1, "%3d > %f\n", rayID, angle);

	distFinal = fmin(distHori, distVert) * angle;

	draw_strip(cub, rayID, distFinal);
}

void	raycaster(t_cub *cub)
{
	float	deltaCam;
	t_vect	src_range;
	t_vect	dst_range;
	int		i;

	// 2D!
	// render_map(cub);
	src_range = set_vector(0, STRIP_COUNT);
	dst_range = set_vector(-FOV / 2, FOV / 2);
	i = -1;
	while (++i != STRIP_COUNT)
	{
		deltaCam = math_map(i, src_range, dst_range);
		cast_ray(cub, cub->cam.yaw + deltaCam, i);
	}
}