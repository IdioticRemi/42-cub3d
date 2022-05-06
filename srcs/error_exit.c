/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:28 by selee             #+#    #+#             */
/*   Updated: 2022/05/06 15:03:14 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message_exit(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	exit_hook(t_cub *cub)
{
	free_map_arr(cub);
	free(cub->info.n_path);
	free(cub->info.s_path);
	free(cub->info.w_path);
	free(cub->info.e_path);
	free(cub->file);
	exit(0);
}
