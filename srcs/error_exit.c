/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:28 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:23:07 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clean_all(t_cub *cub)
{
	free_map_arr(cub);
	free(cub->info.n_path);
	free(cub->info.s_path);
	free(cub->info.w_path);
	free(cub->info.e_path);
	free(cub->file);
	if (cub->screen.ptr)
		mlx_destroy_image(cub->mlx, cub->screen.ptr);
}

void	error_message_exit(t_cub *cub, char *message)
{
	if (cub)
		clean_all(cub);
	ft_putendl_fd("\033[1;31mError\033[0;0m", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	exit_hook(t_cub *cub)
{
	clean_all(cub);
	ft_putendl_fd("", 1);
	exit(0);
}
