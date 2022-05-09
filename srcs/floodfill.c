/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:57:49 by tjolivea          #+#    #+#             */
/*   Updated: 2022/05/09 11:54:17 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	floodfill(char **map, int width, int height, t_vect pos)
{
	int	ret;

	if ((int)pos.x < 0 || (int)pos.x >= width
		|| (int)pos.y < 0 || (int)pos.y >= height)
	{
		return (1);
	}
	if (ft_strchr("0 ", map[(int)pos.x][(int)pos.y]))
	{
		map[(int)pos.x][(int)pos.y] = '.';
		ret = 0;
		ret += floodfill(map, width, height, vector_add(pos, set_vector(1, 0)));
		ret += floodfill(map, width, height, vector_add(pos, set_vector(0, 1)));
		ret += floodfill(map, width, height,
				vector_add(pos, set_vector(-1, 0)));
		ret += floodfill(map, width, height,
				vector_add(pos, set_vector(0, -1)));
		return (fminl(ret, 1));
	}
	return (0);
}
