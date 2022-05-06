/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:39 by selee             #+#    #+#             */
/*   Updated: 2022/05/06 17:25:26 by selee            ###   ########lyon.fr   */
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
	// cub->info.floor = GRAY;
	// cub->info.ceiling = GRAY;
	// cub->info.n_path = ft_strdup("./assets_xpm/pixel_winter64.xpm");
	// cub->info.s_path = ft_strdup("./assets_xpm/pixel_summer64.xpm");
	// cub->info.w_path = ft_strdup("./assets_xpm/pixel_autumn64.xpm");
	// cub->info.e_path = ft_strdup("./assets_xpm/pixel_spring64.xpm");
	// cub->map.column_count = 33;
	// cub->map.row_count = 17;
	// cub->map._array = ft_strdup("        1111111111111111111111111        1000000000110000000000001        1011000001110000000000001        100100000000000000000000111111111101100000111000000000000110000000001100000111011111111111111110111111111011100000010001    11110111111111011101010010001    11000000110101011100000010001    10000000000000001100000010001    10000000000000001101010010001    11000001110101011111011110N0111  11110111 1110101 101111010001    11111111 1111111 111111111111    1                                1                                11111                            ");
	// cub->map._array = ft_strdup("abcabc");
	char *test;

	test = ft_calloc(sizeof(char), cub->map.column_count * cub->map.row_count);
	ft_memset(test, ' ', cub->map.column_count * cub->map.row_count);
	// for (int i = 0; i < cub->map.column_count; i++)
	// {
	// 	for (int j = 0; j < cub->map.row_count; j++)
	// 	{
	// 		test[j * cub->map.column_count + i] = cub->map._array[i * cub->map.row_count + j];
	// 	}
	// }
	// test = cub->map._array;
	// for (int i = 0; i < cub->map.column_count * cub->map.row_count; i++)
	// {
	// 	if (i % cub->map.column_count == 0)
	// 		dprintf(1, "\n");
	// 	dprintf(1, "%c", cub->map._array[i]);
	// }
	// dprintf(1, "\n");

	int width = cub->map.column_count, height = cub->map.row_count;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			*(test + (x * height) + y) = *(cub->map._array + (y * width) + x);
		}
	}
	// for (int i = 0; i < cub->map.column_count * cub->map.row_count; i++)
	// {
	// 	if (i % cub->map.row_count == 0)
	// 		dprintf(1, "\n");
	// 	dprintf(1, "%c", test[i]);
	// }
	free(cub->map._array);
	cub->map._array = test;

	cub->map.array = malloc(sizeof(char *) * cub->map.column_count);
	for (int i = 0; i < cub->map.column_count; i++)
	{
		cub->map.array[i] = &cub->map._array[i * cub->map.row_count];
	}
	// for (int i = 0; i < cub->map.column_count; i++)
	// {
	// 	for (int j = 0; j < cub->map.row_count; j++)
	// 	{
	// 		ft_putchar_fd(cub->map.array[i][j], 1);
	// 	}
	// 	ft_putchar_fd('\n', 1);
	// }
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

uint64_t	ft_get_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	game_loop(t_cub *cub)
{
	last_frame = ft_get_ms();
	draw_background(cub);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
	dprintf(1, "%.0f\r", 1.0 / (((double)ft_get_ms() - (double)last_frame) / 1000.0));
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
	read_cub_file(&cub, map_path);
	check_file(&cub);
	test_parsing(&cub);
	mlx_hook(cub.win, KEYPRESS, 1L << 0, &key_press_event, &cub);
	mlx_hook(cub.win, KEYRELEASE, 1L << 1, &key_release_event, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, &cub);
	mlx_loop(cub.mlx);
	exit_hook(&cub);
}
