#include "cub3d.h"

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




