/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:19:02 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 14:34:01 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_arr(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->map.row_count)
	{
		free(cub->map.array[i]);
		i++;
	}
	free(cub->map.array);
}
