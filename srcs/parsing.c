#include "cub3d.h"

int	convert_color_number(int r, int g, int b)
{
	int	color;

	color = r * (256 * 256) + g * 256 + b;
	return (color);
}

int	get_color_number(char *color_info)
{
	char	**color;
	int	r;
	int	g;
	int	b;

	color = ft_split(color_info, ','); //do i need to handle ' '?
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);

	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_message_exit("invalid color number");
	return (convert_color_number(r, g, b));
}

int	map_check_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	if(ext[0] != '.')
		error_message_exit("Invalid extension");
	i = ft_strlen(filename) - ft_strlen(ext);
	j = 0;
	while (filename[i + j] && ext[j])
	{
		if (filename[i + j] != ext[j])
			error_message_exit("Invalid file extension");
		j++;
	}
	return (1);
}

int	check_valid_character(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (ERROR);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	check_identifier(t_cub *cub, char *str)
{
/* check first letters of the str and identify the identifier*/
	char	id;
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((str[i] == 'N' && str[i + 1] == ' ') || (str[i] == 'N' && str[i + 1] == 'O'))
		id = 'N';
	else if ((str[i] == 'S' && str[i + 1] == ' ') || (str[i] == 'S' && str[i + 1] == 'O'))
		id = 'S';
	else if ((str[i] == 'W' && str[i + 1] == ' ') || (str[i] == 'W' && str[i + 1] == 'E'))
		id = 'W';
	else if ((str[i] == 'E' && str[i + 1] == ' ') || (str[i] == 'E' && str[i + 1] == 'A'))
		id = 'E';
	else if (str[i] == 'F')
		id = 'F';
	else if (str[i] == 'C')
		id = 'C';
	else
		error_message_exit("Invalid identifier");
	return (id);
}

int		save_info(t_cub *cub, char *info_str , char id)
{
// store each info to texture structure by identifier
	int	i;
	
	i = 0;
	if (id == 'N')
		cub->texture.n_path = info_str;
	else if (id == 'S')
		cub->texture.s_path = info_str;
	else if (id == 'W')
		cub->texture.w_path = info_str;
	else if (id == 'E')
		cub->texture.e_path = info_str;
	else if (id == 'F')
		cub->texture.floor = get_color_number(info_str);
	else if (id == 'C')
		cub->texture.ceiling = get_color_number(info_str);

}

// IDとPath切る
int		check_valid_texture_path(t_cub *cub, char *path)
{

	return (0);
}





int		map_read_file(t_cub *cub, char *file_path)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		error_message_exit("Failed to open file");
	while (get_next_line(fd, *line) > 0)
	{
		if (check_valid_character(line) == ERROR)
			return (ERROR);
		
	}
	
}



// 上部の情報　・　下部のMAP どうわける？



