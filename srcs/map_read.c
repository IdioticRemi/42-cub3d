/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:01 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 16:34:18 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_count_row_column(t_cub *cub, int fd)
{
	int		column_count;
	char	buf;

	column_count = 0;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
		{
			cub->map.row_count++;
			if (cub->map.column_count < column_count)
				cub->map.column_count = column_count;
			column_count = 0;
		}
		else
			column_count++;
	}
}

void	map_malloc(t_cub *cub, int fd)
{
	int		i;

	i = 0;
	cub->map.array = NULL;
	map_count_row_column(cub, fd);
	cub->map.array = (char **)malloc(sizeof(char *)
			* cub->map.row_count);
	while (i < cub->map.row_count)
	{
		cub->map.array[i] = (char *)malloc(sizeof(char)
				* cub->map.column_count);
		i++;
	}
}

void	map_read_file(t_cub *cub, char *map_file)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

	i = 0;
	fd = open(map_file, O_RDONLY);
	
	while (get_next_line(fd, &line) > 0)
	{
		printf("check\n");
		j = 0;
		while (j < cub->map.column_count)
		{
			printf("check c: %c", line[j]);
			cub->map.array[i][j] = line[j];
			j++;
		}
		i++;
		free(line);
	}
	// free(line); // error message "pointer being freed was not allocated"
	close(fd);
}

void	map_read_and_check(t_cub *cub, char *map_path)
{
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		error_message_exit("File open failed");
	init_map_value(cub);
	map_malloc(cub, fd);
	close(fd);
	map_read_file(cub, map_path);
	player_get_coord(cub);
	map_check_format(cub);
}
