/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:39 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:20:18 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img(t_cub *cub)
{
	cub->tx.north.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.n_path,
			&cub->keys.key_w, &cub->keys.key_w);
	if (!cub->tx.north.ptr)
		error_message_exit(cub, "Invalid tx name or path.");
	cub->tx.north.addr = mlx_get_data_addr(cub->tx.north.ptr,
			&cub->tx.north.bpp, &cub->tx.north.ln, &cub->tx.north.e);
	cub->tx.south.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.s_path,
			&cub->keys.key_w, &cub->keys.key_w);
	if (!cub->tx.south.ptr)
		error_message_exit(cub, "Invalid tx name or path.");
	cub->tx.south.addr = mlx_get_data_addr(cub->tx.south.ptr,
			&cub->tx.south.bpp, &cub->tx.south.ln, &cub->tx.south.e);
	cub->tx.east.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.e_path,
			&cub->keys.key_w, &cub->keys.key_w);
	if (!cub->tx.east.ptr)
		error_message_exit(cub, "Invalid tx name or path.");
	cub->tx.east.addr = mlx_get_data_addr(cub->tx.east.ptr, &cub->tx.east.bpp,
			&cub->tx.east.ln, &cub->tx.east.e);
	cub->tx.west.ptr = mlx_xpm_file_to_image(cub->mlx, cub->info.w_path,
			&cub->keys.key_w, &cub->keys.key_w);
	if (!cub->tx.west.ptr)
		error_message_exit(cub, "Invalid tx name or path.");
	cub->tx.west.addr = mlx_get_data_addr(cub->tx.west.ptr, &cub->tx.west.bpp,
			&cub->tx.west.ln, &cub->tx.west.e);
	cub->keys.key_w = 0;
}

void	do_floodfill(t_cub *cub)
{
	int	x;
	int	y;

	if (floodfill(cub->map.array, cub->map.w, cub->map.h, vector_multi(
				vector_subs(cub->player.pos, set_vector(
						TILE_SIZE / 2, TILE_SIZE / 2)), 1.0 / TILE_SIZE)))
		error_message_exit(cub, "Input map is not closed.");
	x = -1;
	while (++x < cub->map.w)
	{
		y = -1;
		while (++y < cub->map.h)
			if (cub->map.array[x][y] == '.')
				cub->map.array[x][y] = '0';
	}
}

void	test_parsing(t_cub *cub)
{
	char	*test;
	int		x;
	int		y;

	test = ft_calloc(sizeof(char), cub->map.w * cub->map.h);
	ft_memset(test, ' ', cub->map.w * cub->map.h);
	x = -1;
	while (++x < cub->map.w)
	{
		y = -1;
		while (++y < cub->map.h)
			*(test + (x * cub->map.h) + y) = *(cub->map._array
					+ (y * cub->map.w) + x);
	}
	free(cub->map._array);
	cub->map._array = test;
	cub->map.array = malloc(sizeof(char *) * cub->map.w);
	x = -1;
	while (++x < cub->map.w)
		cub->map.array[x] = &cub->map._array[x * cub->map.h];
	init_player(cub);
	init_img(cub);
	precalc_all(cub);
	do_floodfill(cub);
}

int	game_loop(t_cub *cub)
{
	uint64_t	start;

	start = ft_get_ms();
	if (cub->keys.key_w || cub->keys.key_s || cub->keys.key_a
		|| cub->keys.key_d || cub->keys.key_right || cub->keys.key_left)
	{
		raycaster(cub);
		mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.ptr, 0, 0);
		dprintf(1, "FPS: %.0f.\r", 1.0 / (((double)ft_get_ms() - (
						double)start) / 1000.0));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit(NULL, "Invalid argument");
	map_path = argv[1];
	init_game(&cub);
	read_cub_file(&cub, map_path);
	check_file(&cub);
	test_parsing(&cub);
	raycaster(&cub);
	mlx_put_image_to_window(cub.mlx, cub.win, cub.screen.ptr, 0, 0);
	mlx_hook(cub.win, KEYPRESS, 1L << 0, &key_press_event, &cub);
	mlx_hook(cub.win, KEYRELEASE, 1L << 1, &key_release_event, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, &cub);
	mlx_loop(cub.mlx);
	exit_hook(&cub);
}
