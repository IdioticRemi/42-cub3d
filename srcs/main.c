/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:39 by selee             #+#    #+#             */
/*   Updated: 2022/05/05 12:20:40 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_rgba	mlx_img_pixel_get(t_image *img, int x, int y)
{
	char	*dest;
	t_rgba	color;

	dest = img->addr + (y * img->line_length + x
			* (img->bits_per_pixel / 8));
	color.value = *(unsigned int *)dest;
	return (color);
}

void	precalc_img(t_image *img, t_rgba tab[64][64])
{
	int x;
	int y;

	x = -1;
	while (++x < 64)
	{
		y = -1;
		while (++y < 64)
		{
			tab[x][y] = mlx_img_pixel_get(img, x, y);
			if (x == 32 && y == 32)
				dprintf(1, "color: %X\n", tab[x][y].value);
		}
	}
}

void	precalc_all(t_cub *cub)
{
	precalc_img(&cub->texture.north, cub->texture.n);
	precalc_img(&cub->texture.south, cub->texture.s);
	precalc_img(&cub->texture.east, cub->texture.e);
	precalc_img(&cub->texture.west, cub->texture.w);
}

void	test_parsing(t_cub *cub)
{
	cub->info.floor = BLACK;
	cub->info.ceiling = BLACK;
	cub->info.n_path = ft_strdup("./assets_xpm/pixel_winter64.xpm");
	cub->info.s_path = ft_strdup("./assets_xpm/pixel_summer64.xpm");
	cub->info.w_path = ft_strdup("./assets_xpm/pixel_autumn64.xpm");
	cub->info.e_path = ft_strdup("./assets_xpm/pixel_spring64.xpm");
	cub->map.column_count = 8;
	cub->map.row_count = 8;
	cub->map._array = ft_strdup("11111111101E0001100001111000000111100001100000011001000111111111");
	cub->map.array = malloc(sizeof(char *) * cub->map.column_count);
	for (int i = 0; i < cub->map.column_count; i++)
	{
		cub->map.array[i] = &cub->map._array[i * cub->map.column_count];
	}
	for (int i = 0; i < cub->map.column_count; i++)
	{
		for (int j = 0; j < cub->map.row_count; j++)
		{
			ft_putchar_fd(cub->map.array[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}

	cub->texture.north.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.n_path, &cub->keys.key_w, &cub->keys.key_w);
	cub->texture.north.addr = mlx_get_data_addr(cub->texture.north.ptr, &cub->texture.north.bits_per_pixel, &cub->texture.north.line_length, &cub->texture.north.endian);

	cub->texture.south.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.s_path, &cub->keys.key_w, &cub->keys.key_w);
	cub->texture.south.addr = mlx_get_data_addr(cub->texture.south.ptr, &cub->texture.south.bits_per_pixel, &cub->texture.south.line_length, &cub->texture.south.endian);

	cub->texture.east.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.e_path, &cub->keys.key_w, &cub->keys.key_w);
	cub->texture.east.addr = mlx_get_data_addr(cub->texture.east.ptr, &cub->texture.east.bits_per_pixel, &cub->texture.east.line_length, &cub->texture.east.endian);

	cub->texture.west.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.w_path, &cub->keys.key_w, &cub->keys.key_w);
	cub->texture.west.addr = mlx_get_data_addr(cub->texture.west.ptr, &cub->texture.west.bits_per_pixel, &cub->texture.west.line_length, &cub->texture.west.endian);

	cub->keys.key_w = 0;
	cub->keys.key_s= 0;
	cub->keys.key_a = 0;
	cub->keys.key_d = 0;
	cub->keys.key_right = 0;
	cub->keys.key_left = 0;
	
	init_player(cub);
	precalc_all(cub);
}

int	game_loop(t_cub *cub)
{
	draw_background(cub);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	char	*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	init_game(&cub);
	test_parsing(&cub);
	mlx_hook(cub.win, KEYPRESS, 1L << 0, &key_press_event, &cub);
	mlx_hook(cub.win, KEYRELEASE, 1L << 1, &key_release_event, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, &cub);
	mlx_loop(cub.mlx);
}
