#include "cub3d.h"

int	exit_hook(void)
{
	exit(0);
}

// void	player_at_exit(t_cub *cub)
// {
// 	if (player_touched_exit(cub))
// 	{
// 		if (collec_all_collected(cub))
// 			cub->status = GAME_END;
// 		else if (!(collec_all_collected(cub)))
// 			cub->status = GAME_CONTINUE;
// 	}
// }
