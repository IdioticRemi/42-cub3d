#include "cub3d.h"


void	error_message_exit(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	map_check_file_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	if (ext[0] != '.')
		return (error_message_exit("Invalid file extension");
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
	//check NO/SO/WE/EA
	//check if map is walled
	//check 

}