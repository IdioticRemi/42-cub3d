/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_old.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:18:58 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:05:00 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_map_content(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_strchr("NSWE01 ", line[i]))
			return (0);
	return (1);
}

t_vect	check_lines(t_cub *cub, char **lines, int *pc, int *i)
{
	t_vect	m;

	m.x = 0;
	m.y = 0;
	*pc = 0;
	*i = -1;
	while (lines[++*i])
	{
		if (*i < 6 && ((*i < 5 && !lines[*i + 1])
				|| check_texture_info(cub, lines[*i])))
			error_message_exit(cub, "Texture format is wrong.");
		if (*i == 6 && !(cub->info.c_parsed && cub->info.f_parsed))
			error_message_exit(cub, "Missing floor or ceiling color.");
		if (*i >= 6)
		{
			if (!(valid_map_content(lines[*i])))
				error_message_exit(cub, "Invalid map.");
			*pc += ft_strcnt(lines[*i], 'N') + ft_strcnt(lines[*i], 'S');
			*pc += ft_strcnt(lines[*i], 'W') + ft_strcnt(lines[*i], 'E');
			if (ft_strlen(lines[*i]) > m.x)
				m.x = ft_strlen(lines[*i]);
			m.y++;
		}
	}
	return (m);
}

void	check_file(t_cub *cub)
{
	char	**lines;
	t_vect	m;
	int		i;
	int		pc;

	lines = ft_split(cub->file, '\n');
	if (!lines)
		error_message_exit(cub, "Malloc error.");
	m = check_lines(cub, lines, &pc, &i);
	if (i == 6)
		error_message_exit(cub, "Could not find a map in file.");
	cub->map._array = malloc(sizeof(char) * (int)m.x * (int)m.y + 1);
	ft_memset(cub->map._array, ' ', (int)m.x * (int)m.y);
	cub->map._array[(int)m.x * (int)m.y] = '\0';
	i = 5;
	while (lines[++i])
		ft_memcpy(cub->map._array + ((int) m.x * (i - 6)),
			lines[i], ft_strlen(lines[i]));
	cub->map.w = (int)m.x;
	cub->map.h = (int)m.y;
	if (pc != 1)
		error_message_exit(cub, "You need at least/most 1 player!");
	free_char_array(lines);
}

int	check_file_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	if (ext[0] != '.')
		error_message_exit(NULL, "Invalid file extension");
	i = ft_strlen(filename) - ft_strlen(ext);
	j = 0;
	while (filename[i + j] && ext[j])
	{
		if (filename[i + j] != ext[j])
			error_message_exit(NULL, "File name is not valid for this project");
		j++;
	}
	return (1);
}
