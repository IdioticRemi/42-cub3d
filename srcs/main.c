/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:56 by selee             #+#    #+#             */
/*   Updated: 2022/04/07 23:40:17 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_cub *cub)
{
	if (cub->status == GAME_PLAY)
	{
		put_map_to_win(cub);
		put_map_grid(cub);
		put_player_pixel(cub);
		// draw_line(cub, cub->player.pos_x, cub->player.pos_y, cub->player.pos_y + 10, YELLOW);
		put_ray(cub);
	}
	return (0);
}
/*
	for (int x = 0; x < cub->win_width; x++)
	{
		double cameraX = 2 * x / (double)cub->win_width - 1;
		double rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		double rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;

		int mapX = (int)cub->player.pos_x; //location of current ray
		int	mapY = (int)cub->player.pos_y;


		double deltaDistX = fabs(1 / rayDirX); //absolute value
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		double sideDistX, sideDistY;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player.pos_y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side =0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// if (cub->map.array[mapX][mapY] > 0)
			// 	hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - cub->player.pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cub->player.pos_y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(cub->win_height / perpWallDist);

		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;

	}
	}

	return (0);
}

int	main_loop(t_cub *cub)
{
	for (int x = 0; x < cub->win_width; x++)
	{
		double cameraX = 2 * x / (double)cub->win_width - 1;
		double rayDirX = cub->player.dir_x + cub->player.plane_x * cameraX;
		double rayDirY = cub->player.dir_y + cub->player.plane_y * cameraX;

		int mapX = (int)cub->player.pos_x; //location of current ray
		int	mapY = (int)cub->player.pos_y;

		double sideDistX, sideDistY;

		double deltaDistX = fabs(1 / rayDirX); //absolute value
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cub->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cub->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub->player.pos_y) * deltaDistY;
		}


		int lineHeight = (int)(cub->win_height / perpWallDist);

		int drawStart = -lineHeight / 2 + cub->win_height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + cub->win_height / 2;
		if (drawEnd >= cub->win_height)
			drawEnd = cub->win_height - 1;

	}
}
*/

int	main(int argc, char **argv)
{
	char		*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	cub.status = GAME_PLAY;
	map_check_file_extension(map_path, ".ber");
	map_read_and_check(&cub, map_path);
	init_game(&cub);
	init_game_img (&cub);
	mlx_hook(cub.win, EVENT_KEY_PRESS, 1L << 0, &key_input, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, 0);
	mlx_loop(cub.mlx);
}
