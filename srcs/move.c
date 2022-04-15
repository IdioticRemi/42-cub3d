/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyounglee <seoyounglee@student.42lyon    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:19:26 by selee             #+#    #+#             */
/*   Updated: 2022/04/15 23:12:26 by seoyounglee      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_cub *cub, float rot_angle)
{
	t_fov	f;
	f = cub->fov;
	cub->fov.dir.x = f.dir.x * cos(rot_angle) - f.dir.y * sin(rot_angle);
	cub->fov.dir.y = f.dir.x * sin(rot_angle) + f.dir.y * cos(rot_angle);
}
