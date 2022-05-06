/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:40:14 by selee             #+#    #+#             */
/*   Updated: 2022/05/06 14:47:38 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*skip_spaces(const char *s)
{
	while (s && *s == ' ')
		s++;
	return (s);
}

int	ft_strcnt(const char *s, char c)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
			cnt++;
	return (cnt);
}

int	is_number(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	is_valid_color(const char *s)
{
	int		r;
	char	**tmp;

	r = 1;
	tmp = ft_split(s, ',');
	if (!(tmp[0] && tmp[1] && tmp[2]))
	{
		free_char_array(tmp);
		return (0);
	}
	if (!((strlen(tmp[0]) < 3 || (strlen(tmp[0]) == 3
					&& ft_strcmp(tmp[0], "256") < 0)) && is_number(tmp[0])))
		r = 0;
	if (!((strlen(tmp[1]) < 3 || (strlen(tmp[1]) == 3
					&& ft_strcmp(tmp[1], "256") < 0)) && is_number(tmp[1])))
		r = 0;
	if (!((strlen(tmp[2]) < 3 || (strlen(tmp[2]) == 3
					&& ft_strcmp(tmp[2], "256") < 0)) && is_number(tmp[2])))
		r = 0;
	free_char_array(tmp);
	return (r);
}
