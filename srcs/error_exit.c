#include "cub3d.h"

// free all before exit

void	error_message_exit(char *message)
{
	ft_putendl_fd("Error ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int	exit_hook(void)
{
	exit(0);
}
