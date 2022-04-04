/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 14:38:52 by selee             #+#    #+#             */
/*   Updated: 2022/04/04 14:43:37 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
