/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:49:53 by selee             #+#    #+#             */
/*   Updated: 2022/05/04 13:12:02 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vect	set_vector(double x, double y)
{
	t_vect	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vect	vector_add(t_vect vec, t_vect to_add)
{
	vec.x += to_add.x;
	vec.y += to_add.y;
	return (vec);
}

t_vect	vector_subs(t_vect vec, t_vect to_sub)
{
	vec.x -= to_sub.x;
	vec.y -= to_sub.y;
	return (vec);
}

t_vect	vector_multi(t_vect vec, double num)
{
	vec.x *= num;
	vec.y *= num;
	return (vec);
}
