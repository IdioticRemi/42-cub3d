/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:15:29 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:11:47 by tjolivea         ###   ########.fr       */
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
		error_message_exit(cub, strerror(errno));
	cub->file = ft_calloc(sizeof(char), 1);
	if (!cub->file)
		error_message_exit(cub, "Malloc error.");
	read_count = 99999;
	while (read_count == 99999)
	{
		read_count = read(fd, buf, 99999);
		buf[read_count] = '\0';
		tmp = cub->file;
		cub->file = ft_strjoin(cub->file, buf);
		if (!cub->file)
			error_message_exit(cub, "Malloc error.");
		free(tmp);
	}
	return (0);
}

unsigned int	get_color(t_cub *cub, const char *info)
{
	t_rgba	color;
	char	**tmp;

	if (!is_valid_color(info))
		error_message_exit(cub, "Invalid color format.");
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
	if (!cub->info.n_path && line[0] == 'N' && ((line[1] == ' ')
			|| (line[1] == 'O' && line[2] == ' ')))
		cub->info.n_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.s_path && line[0] == 'S' && ((line[1] == ' ')
			|| (line[1] == 'O' && line[2] == ' ')))
		cub->info.s_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.w_path && line[0] == 'W' && ((line[1] == ' ')
			|| (line[1] == 'E' && line[2] == ' ')))
		cub->info.w_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (!cub->info.e_path && line[0] == 'E' && ((line[1] == ' ')
			|| (line[1] == 'A' && line[2] == ' ')))
		cub->info.e_path = ft_strdup(skip_spaces(ft_strchr(line, ' ')));
	else if (line[0] == 'F' && line[1] == ' ' && ft_strcnt(line, ',') == 2)
		cub->info.floor = get_color(cub, skip_spaces(ft_strchr(line, ' ')));
	else if (line[0] == 'C' && line[1] == ' ' && ft_strcnt(line, ',') == 2)
		cub->info.ceiling = get_color(cub, skip_spaces(ft_strchr(line, ' ')));
	else
		return (1);
	return (0);
}
