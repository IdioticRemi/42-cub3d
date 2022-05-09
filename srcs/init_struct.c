/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:35 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:19:50 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_map(t_cub *cub)
{
	cub->map.array = NULL;
	cub->map._array = NULL;
	cub->map.h = 0;
	cub->map.w = 0;
}

void	init_info(t_cub *cub)
{
	cub->info.n_path = NULL;
	cub->info.s_path = NULL;
	cub->info.w_path = NULL;
	cub->info.e_path = NULL;
	cub->info.floor = 0;
	cub->info.f_parsed = 0;
	cub->info.ceiling = 0;
	cub->info.c_parsed = 0;
	cub->keys.key_w = 0;
	cub->keys.key_s = 0;
	cub->keys.key_a = 0;
	cub->keys.key_d = 0;
	cub->keys.key_right = 0;
	cub->keys.key_left = 0;
}

static void	init_camera(t_cub *cub, char dir)
{
	if (dir == 'N')
		cub->cam.yaw = PI / 2 * 3;
	else if (dir == 'E')
		cub->cam.yaw = 0;
	else if (dir == 'S')
		cub->cam.yaw = PI / 2;
	else if (dir == 'W')
		cub->cam.yaw = PI;
	cub->cam.yaw -= FOV / 2;
}

void	init_player(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.h)
	{
		j = 0;
		while (j < cub->map.w)
		{
			if (ft_strchr("NSWE", cub->map.array[j][i]))
			{
				cub->player.pos = set_vector(j * TILE_SIZE + (TILE_SIZE / 2),
						i * TILE_SIZE + (TILE_SIZE / 2));
				init_camera(cub, cub->map.array[j][i]);
				cub->map.array[j][i] = '0';
			}
			j++;
		}
		i++;
	}
}

void	init_game(t_cub *cub)
{
	init_struct_map(cub);
	init_info(cub);
	cub->mlx = mlx_init();
	cub->win = mlx_new_window(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	cub->screen.ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->screen.addr = mlx_get_data_addr(cub->screen.ptr,
			&cub->screen.bpp,
			&cub->screen.ln, &cub->screen.e);
}
