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

float	math_map(float x, t_vect src_range, t_vect dst_range)
{
	float	out;

	if (x > src_range.y)
		return (dst_range.y);
	else if (x < src_range.x)
		return (dst_range.x);
	out = src_range.x + ((dst_range.y - dst_range.x)
			/ (src_range.y - src_range.x)) * (x - src_range.x);
	return (out);
}

float	math_dist(t_vect origin, t_vect arrival)
{
	float	dist;

	dist = sqrtf((arrival.x - origin.x) * (arrival.x - origin.x)
			+ (arrival.y - origin.y) * (arrival.y - origin.y));
	return (dist);
}
