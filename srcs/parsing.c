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
			return (0);
		i++;
	}
	return (1);
}





