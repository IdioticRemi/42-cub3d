#include "cub3d.h"

void	bresenham(t_cub *cub, t_vect src, t_vect dest, int color)
{
	double	stepX;
	double	stepY;
	int i;

	// dprintf(1, "%f %f | %f %f\n", src.x, src.y, dest.x, dest.y);
	src.x *= 100 * TILE_SIZE;
	src.y *= 100 * TILE_SIZE;
	dest.x *= 100 * TILE_SIZE;
	dest.y *= 100 * TILE_SIZE;
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

void	render_2d(t_cub *cub, t_dda dda)
{
	bresenham(cub, cub->player.pos, 
		set_vector(cub->player.pos.x + cos(cub->cam.yaw) * dda.perpWallDist, cub->player.pos.y + sin(cub->cam.yaw) * dda.perpWallDist), BLACK);
}

void	render_map(t_cub *cub)
{
	for (int x = 0; x < cub->map.column_count; x++)
	{
		for (int y = 0; y < cub->map.row_count; y++)
		{
			int shiftX = x * 100;
			int shiftY = y * 100;
			char tile = cub->map.array[x][y];
			char obstacle = tile == '1';
			for (int a = 0; a < 98; a++)
			{
				for (int b = 0; b < 98; b++)
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

void	cast_ray(t_cub *cub, float angle)
{
	int		max_dist;
	int		dist;
	float	aTan;
	float	temp;
	t_dda	dda;

	while (angle > 2 * PI)
		angle -= 2 * PI;
	while (angle < 0)
		angle += 2 * PI;
	aTan = -1.0 / tan(angle); 
	dist = 0;
	max_dist = 8;

	dda.dir = set_vector(cos(angle), sin(angle));
	// bresenham(cub, cub->player.pos, vector_add(cub->player.pos, dda.dir), RED);
	// HORIZONTAL
	temp = cub->player.pos.y;
	while (temp > TILE_SIZE)
		temp -= TILE_SIZE;
	if (angle < PI)
	{
		// FACING UP
		dda.dir.y = cub->player.pos.y + TILE_SIZE - temp;
		dda.dir.x = cub->player.pos.x + ((TILE_SIZE - temp) / tan(angle));
		dda.offset = set_vector(TILE_SIZE * aTan, -TILE_SIZE);
	}
	if (angle > PI)
	{
		// FACING DOWN
		dda.dir.y = cub->player.pos.y - temp;
		dda.dir.x = cub->player.pos.x - ((TILE_SIZE - temp) / tan(angle));
		dda.offset = set_vector(TILE_SIZE * aTan, TILE_SIZE);
	}
	if (angle == 0 || angle == 2 * PI)
	{
		dist = max_dist;
		dda.dir = cub->player.pos;
	}
	// bresenham(cub, cub->player.pos, dda.dir, BLUE);
	while (dist < max_dist)
	{
		dda.mapX = dda.dir.x / TILE_SIZE;
		dda.mapY = dda.dir.y / TILE_SIZE;
		if (dda.mapX >= 0 && dda.mapX < cub->map.column_count && dda.mapY >= 0 && dda.mapY < cub->map.row_count && cub->map.array[dda.mapX][dda.mapY] == '1')
			dist = 8;
		else
		{
			// bresenham(cub, dda.dir, vector_add(dda.dir, dda.offset), PINK);
			dda.dir = vector_add(dda.dir, dda.offset);
			dist++;
		}
	}

	// dprintf(1, "mapX: %d | mapY: %d\n", dda.mapX, dda.mapY);
	// dprintf(1, "x: %f | y: %f\n", dda.dir.x, dda.dir.y);
	bresenham(cub, cub->player.pos, dda.dir, BLUE);
}

float	math_map(float x, t_vect src_range, t_vect dst_range)
{
	float out;

	out = src_range.x + ((dst_range.y - dst_range.x) / (src_range.y - src_range.x)) * (x - src_range.x);

	return (out);
}

void	raycaster(t_cub *cub)
{
	float	deltaCam;
	t_vect	src_range;
	t_vect	dst_range;
	int		i;

	render_map(cub);
	src_range = set_vector(0, STRIP_COUNT);
	dst_range = set_vector(-FOV / 2, FOV / 2);
	i = -1;
	while (++i != STRIP_COUNT)
	{
		deltaCam = math_map(i, src_range, dst_range);
		cast_ray(cub, cub->cam.yaw + deltaCam);
	}
}