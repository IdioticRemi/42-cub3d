/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:15:29 by selee             #+#    #+#             */
/*   Updated: 2022/05/06 17:30:29 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_cub_file(t_cub *cub, char *filename)
{
	int		fd;
	int		read_count;
	char	*tmp;
	char	buf[10000];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message_exit(strerror(errno));
	cub->file = ft_calloc(sizeof(char), 1);
	if (!cub->file)
		error_message_exit("Malloc error.");
	read_count = 99999;
	while (read_count == 99999)
	{
		read_count = read(fd, buf, 99999);
		buf[read_count] = '\0';
		tmp = cub->file;
		cub->file = ft_strjoin(cub->file, buf);
		if (!cub->file)
			error_message_exit("Malloc error.");
		free(tmp);
	}
	return (0);
}

unsigned int	get_color(const char *info)
{
	t_rgba	color;
	char	**tmp;

	if (!is_valid_color(info))
		error_message_exit("Invalid color format.");
	tmp = ft_split(info, ',');
	color.r = ft_atoi(skip_spaces(tmp[0]));
	color.g = ft_atoi(skip_spaces(tmp[1]));
	color.b = ft_atoi(skip_spaces(tmp[2]));
	color.a = 0;
	free_char_array(tmp);
	return (color.value);
}

int	check_texture_info(t_cub *cub, char *line)
{
	if (ft_strlen(line) < 3)
		return (1);
	if (!cub->info.n_path && line[0] == 'N' && ((line[1] == ' ') || (line[1] == 'O' && line[2] == ' ')))
		cub->info.n_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.s_path && line[0] == 'S' && ((line[1] == ' ') || (line[1] == 'O' && line[2] == ' ')))
		cub->info.s_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.w_path && line[0] == 'W' && ((line[1] == ' ') || (line[1] == 'E' && line[2] == ' ')))
		cub->info.w_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.e_path && line[0] == 'E' && ((line[1] == ' ') || (line[1] == 'A' && line[2] == ' ')))
		cub->info.e_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (line[0] == 'F' && line[1] == ' ' && ft_strcnt(line, ',') == 2)
		cub->info.floor = get_color(skip_spaces(ft_strchr(line, ' ')));
	else if (line[0] == 'C' && line[1] == ' ' && ft_strcnt(line, ',') == 2)
		cub->info.ceiling = get_color(skip_spaces(ft_strchr(line, ' ')));
	else
		return (1);
	return (0);
}

int		valid_map_content(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_strchr("NSWE01 ", line[i]))
			return (0);
	return (1);
}


void	check_file(t_cub *cub)
{
	char	**lines;
	int		i;
	int		pc;
	int		x;
	int		y;

	lines = ft_split(cub->file, '\n');
	if (!lines)
		error_message_exit("Malloc error.");
	pc = 0;
	i = -1;
	x = 0;
	y = 0;
	while (lines[++i])
	{
		if (i < 6 && ((i < 5 && !lines[i + 1]) || check_texture_info(cub, lines[i])))
			error_message_exit("Texture format is wrong.");
		if (i >= 6)
		{
			if (!(valid_map_content(lines[i])))
				error_message_exit("Invalid map.");
			pc += ft_strcnt(lines[i], 'N') + ft_strcnt(lines[i], 'S');
			pc += ft_strcnt(lines[i], 'W') + ft_strcnt(lines[i], 'E');
			if (ft_strlen(lines[i]) > x)
				x = ft_strlen(lines[i]);
			y++;
		}
	}
	if (i == 6)
		error_message_exit("Could not find a map in file.");
	cub->map._array = malloc(sizeof(char) * x * y + 1);
	ft_memset(cub->map._array, ' ', x * y);
	cub->map._array[x * y] = '\0';
	i = 5;
	while (lines[++i])
	{
		ft_memcpy(cub->map._array + (x * (i - 6)), lines[i], ft_strlen(lines[i]));
	}
	cub->map.column_count = x;
	cub->map.row_count = y;
	if (pc != 1)
		error_message_exit("You need at least/most 1 player!");
	dprintf(1, "no:%s\n", cub->info.n_path);
	dprintf(1, "so:%s\n", cub->info.s_path);
	dprintf(1, "we:%s\n", cub->info.w_path);
	dprintf(1, "ea:%s\n", cub->info.e_path);
	dprintf(1, "f :%X\n", cub->info.floor);
	dprintf(1, "c :%X\n", cub->info.ceiling);
	free_char_array(lines);
}
