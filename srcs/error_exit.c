#include "cub3d.h"

// free all before exit

void	error_message_exit(char *message)
{
	ft_putendl_fd("Error ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	exit_hook(t_cub *cub)
{
	free_map_arr(cub);
	exit(0);
}
