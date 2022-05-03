// #include "cub3d.h"

// void	bresenham(t_cub *cub, t_vect src, t_vect dest, int color)
// {
// 	double	stepX;
// 	double	stepY;
// 	int i;

// 	dprintf(1, "%f %f | %f %f\n", src.x, src.y, dest.x, dest.y);
// 	src.x *= 100 * TILE_SIZE;
// 	src.y *= 100 * TILE_SIZE;
// 	dest.x *= 100 * TILE_SIZE;
// 	dest.y *= 100 * TILE_SIZE;
// 	stepX = dest.x - src.x;
// 	stepY = dest.y - src.y;
// 	i = fmax(fabs(stepX), fabs(stepY));
// 	stepX /= i;
// 	stepY /= i;
// 	while ((int)(src.x - dest.x) || (int)(src.y - dest.y))
// 	{
// 		if (!(src.x >= SCREEN_WIDTH || src.y >= SCREEN_HEIGHT || src.x < 0 || src.y < 0))
// 			mlx_img_pixel_put(cub, src.x, src.y, color);
// 		src.x += stepX;
// 		src.y += stepY;
// 	}
// }

// void	get_side_dist_and_step(t_dda *dda, t_player *player)
// {
// 	if (dda->dir.x < 0)
// 	{
// 		dda->step_x = -1;
// 		dda->side_distX = (player->pos.x - dda->mapX) * dda->delta_distX;
// 	}
// 	else
// 	{
// 		dda->step_x = 1;
// 		dda->side_distX = (dda->mapX + 1.0 - player->pos.x) * dda->delta_distX;
// 	}
// 	if (dda->dir.y < 0)
// 	{
// 		dda->step_y = -1;
// 		dda->side_distY = (player->pos.y - dda->mapY) * dda->delta_distY;
// 	}
// 	else
// 	{
// 		dda->step_y = 1;
// 		dda->side_distY = (dda->mapY + 1.0 - player->pos.y) * dda->delta_distY;
// 	}
// }

// void	dda_algo(t_dda *dda, t_map *map)
// {
// 	while (!dda->hit)
// 	{
// 		if (dda->side_distX < dda->side_distY)
// 		{
// // printf("[x] sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
// 			dda->side_distX += dda->delta_distX;
// 			dda->mapX += dda->step_x;
// 			dda->side_hit = 0;
// // printf("[x]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);
// 		}
// 		else
// 		{
// // printf("[y]sideX1: %f | sideY1: %f | mapX1: %d | mapY1: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

// 			dda->side_distY += dda->delta_distY;
// 			dda->mapY += dda->step_y;
// 			dda->side_hit = 1;
// // printf("[y]sideX2: %f | sideY2: %f | mapX2: %d | mapY2: %d\n", ray->side_distX, ray->side_distY, ray->mapX, ray->mapY);

// 		}
// 		if (map->array[dda->mapX][dda->mapY] > 0)
// 			dda->hit = 1;
// 	}
// }

// void	render_ray(t_cub *cub, int ray_index, t_dda dda)
// {
// 	int x;
// 	int len;
// 	int i;
// 	int j;

// 	x = ray_index * STRIP_WIDTH;
// 	len = SCREEN_HEIGHT / dda.perpWallDist;
// 	if (len < 50)
// 		len = 50;
// 	if (len > SCREEN_HEIGHT)
// 		len = SCREEN_HEIGHT;

// 	i = -1;
// 	while (++i < STRIP_WIDTH)
// 	{
// 		j = -1;
// 		while (++j < len)
// 		{
// 			if (dda.side_hit == 0)
// 				mlx_img_pixel_put(cub, x + i, SCREEN_HEIGHT / 2 - len / 2 + j, PINK);
// 			else
// 				mlx_img_pixel_put(cub, x + i, SCREEN_HEIGHT / 2 - len / 2 + j, BLACK);
// 		}
// 	}
// }
// void	render_map(t_cub *cub)
// {
// 	for (int x = 0; x < cub->map.column_count; x++)
// 	{
// 		for (int y = 0; y < cub->map.row_count; y++)
// 		{
// 			int shiftX = x * 100;
// 			int shiftY = y * 100;
// 			char tile = cub->map.array[x][y];
// 			char obstacle = tile == '1';
// 			for (int a = 0; a < 100; a++)
// 			{
// 				for (int b = 0; b < 100; b++)
// 				{
// 					if (obstacle)
// 						mlx_img_pixel_put(cub, shiftX + a, shiftY + b, BLACK);
// 					else
// 						mlx_img_pixel_put(cub, shiftX + a, shiftY + b, WHITE);
// 				}
// 			}
// 		}
// 	}
// }

// void	render_2d(t_cub *cub, t_dda dda)
// {
// 	bresenham(cub, cub->player.pos, 
// 		set_vector(cub->player.pos.x + cos(cub->cam.yaw) * dda.perpWallDist, cub->player.pos.y + sin(cub->cam.yaw) * dda.perpWallDist), BLACK);
// }

// void	raycaster(t_cub *cub)
// {
// 	int	x;
// 	float ratioX;
// 	t_dda dda;

// 	x = 0;
// 	while (x < STRIP_COUNT)
// 	{
// 		ratioX = ((float)x / ((float)STRIP_COUNT));
// 		//dprintf(1, "%f | rad: %f\n", ratioX, 2 * ratioX * FOV - 1);
// 		dda.dir.x = cos(cub->cam.yaw + ((ratioX * FOV)));
// 		dda.dir.y = sin(cub->cam.yaw + ((ratioX * FOV)));
// 		// dprintf(1, "%d | angle: %f\n", x, acos(dda.dir.x) / PI * 180);
// 		dda.mapX = cub->player.pos.x / TILE_SIZE;
// 		dda.mapY = cub->player.pos.y / TILE_SIZE;

// 		dda.delta_distX = sqrt(1 + (dda.dir.y * dda.dir.y) / (dda.dir.x * dda.dir.x));
// 		dda.delta_distY = sqrt(1 + (dda.dir.x * dda.dir.x) / (dda.dir.y * dda.dir.y));

// 		dda.hit = 0;

// 		get_side_dist_and_step(&dda, &cub->player);
// 		dda_algo(&dda, &cub->map);
// 		if (dda.side_hit == 0)
// 			dda.perpWallDist = (dda.mapX - cub->player.pos.x + (1 - dda.step_x) / 2) / dda.dir.x;
// 		else
// 			dda.perpWallDist = (dda.mapY - cub->player.pos.y + (1 - dda.step_y) / 2) / dda.dir.y;
// 		render_ray(cub, x, dda);
// 		x++;
// 	}
// 	render_map(cub);
// 	render_2d(cub, dda);
// }
