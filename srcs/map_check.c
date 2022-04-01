#include "cub3d.h"

void	error_message_exit(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

//check identifier and save to the structure
int		check_element(t_cub *cub, int fd)
{
	//read from the file and check identifier
	//malloc structure's _path array;

	int	i;

	i = 0;
	while ()



}


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

void	map_malloc(t_cub *cub, int fd)
{
	int	i;

	i = 0;
	cub->map.array = NULL;
	
	cub->map.array = (char **)malloc(sizeof(char *) * cub->map.row_count);
	if (!cub->map.array)
		error_message_exit("Allocation fail");
	while (i < cub->map.row_count)
	{
		cub->map.array[i] = (char *malloc())
		i++;
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
		if (filename[i + j ] != ext[j])
			error_message_exit("Invalid file");
		j++;
	}
	return (EXIT_SUCCESS);
}

int map_check(t_cub *cub)
{
	
	//check NO/SO/WE/EA identifier
	//check texture paths
	//check ceiling and floor format
	//check if map is walled
	//check valid character; 0, 1, NSWE	
}

void	map_read_file(t_cub *cub, char *file)
{
	char	*line;
	int		i;
	int		j;
	int		fd;

	i = 0;
	fd = open(file, O_RDONLY);
	while ()
}