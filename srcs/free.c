/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:15 by selee             #+#    #+#             */
/*   Updated: 2022/05/02 16:47:57 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_char_array(char **arr)
{
	int		i;
	
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/* あとでこれ消す。上のと重複してる　*/
void	free_map_arr(t_cub *cub)
{
	free(cub->map.array);
	free(cub->map._array);
}

void	free_texture_info(t_cub *cub);
void	free_all(t_cub *cub);



