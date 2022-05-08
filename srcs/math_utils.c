/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:29:20 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 17:29:38 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	math_dist(t_vect origin, t_vect arrival)
{
	double	dist;

	dist = sqrt((arrival.x - origin.x) * (arrival.x - origin.x)
			+ (arrival.y - origin.y) * (arrival.y - origin.y));
	return (dist);
}
