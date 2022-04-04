#include "cub3d.h"

//check identifier and save to the structure
// int		check_element(t_cub *cub, int fd)
// {
// 	read from the file and check identifier
// 	malloc structure's _path array;

// }

void	map_cout_row_column(t_cub *cub, int fd)
{
	int		column_count;
	char	buf;

	column_count = 0;
	while(read(fd, &buf, 1) > 0)
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

// int map_check(t_cub *cub)
// {
	
// 	//check NO/SO/WE/EA identifier
// 	//check texture paths
// 	//check ceiling and floor format
// 	//check if map is walled
// 	//check valid character; 0, 1, NSWE	
// }


int	map_is_rectangular(t_cub *cub, int line_length)
{
	if (line_length != cub->map.column_count)
		return (0);
	return (1);
}

int	map_is_walled(t_cub *cub)
{
	int		i;
	int		row;
	int		col;

	row = cub->map.row_count;
	col = cub->map.column_count;
	i = 0;
	while (i < col)
	{
		if (cub->map.array[0][i] != '1' || cub->map.array[row - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < row)
	{
		if (cub->map.array[i][0] != '1' || cub->map.array[i][col - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	map_check_format(t_cub *cub)
{
	if (cub->map.row_count == cub->map.column_count)
		error_message_exit("Map is not rectangular");
	if (!map_is_walled(cub))
		error_message_exit("Map is not walled");
}
