#include "cub3d.h"

void	error_message_exit(char *message)
{
	ft_putendl_fd("Error ", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}
