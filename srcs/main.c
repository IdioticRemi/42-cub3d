/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:39 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 12:55:52 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	test_parsing(t_cub *cub)
{
	cub->info.floor = PINK;
	cub->info.ceiling = BLUE;

	cub->info.n_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.s_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.w_path = ft_strdup("./assets_xpm/black_square32.xpm");
	cub->info.e_path = ft_strdup("./assets_xpm/black_square32.xpm");

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

	cub->keys.key_w = 0;
	cub->keys.key_s= 0;
	cub->keys.key_a = 0;
	cub->keys.key_d = 0;
	cub->keys.key_right = 0;
	cub->keys.key_left = 0;
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
	char		*map_path;
	t_cub	cub;

	if (argc != 2)
		error_message_exit("Invalid argument");
	map_path = argv[1];
	test_parsing(&cub);
	init_game(&cub);
	// map_check_file_extension(map_path, ".cub");
	// map_read_and_check(&cub, map_path);
	mlx_hook(cub.win, KEYPRESS, 1L << 0, &key_press_event, &cub);
	mlx_hook(cub.win, KEYRELEASE, 1L << 1, &key_release_event, &cub);
	mlx_loop_hook(cub.mlx, &game_loop, &cub);
	mlx_hook(cub.win, EVENT_EXIT, 0, exit_hook, &cub);
	mlx_loop(cub.mlx);
}
