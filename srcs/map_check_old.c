/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:58 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 15:41:38 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_check_file_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	if (ext[0] != '.')
		error_message_exit("Invalid file extension");
	i = ft_strlen(filename) - ft_strlen(ext);
	j = 0;
	while (filename[i + j] && ext[j])
	{
		if (filename[i + j] != ext[j])
			error_message_exit("Invalid file");
		j++;
	}
	return (1);
}

void	map_check_format(t_cub *cub)
{
	if (cub->map.row_count == cub->map.column_count)
		error_message_exit("Map is not rectangular");

}
