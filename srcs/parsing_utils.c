/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjolivea <tjolivea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:40:14 by selee             #+#    #+#             */
/*   Updated: 2022/05/09 12:11:23 by tjolivea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *s)
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

char	*handle_end_space(char *s)
{
	char	*bef;

	bef = s;
	while (s && *s && *s != ' ')
		s++;
	*s = '\0';
	return (bef);
}

int	is_valid_color(const char *s)
{
	int		r;
	char	**tmp;
	char	*vals[3];

	r = 1;
	tmp = ft_split(s, ',');
	if (!(tmp[0] && tmp[1] && tmp[2]))
	{
		free_char_array(tmp);
		return (0);
	}
	vals[0] = handle_end_space(skip_spaces(tmp[0]));
	vals[1] = handle_end_space(skip_spaces(tmp[1]));
	vals[2] = handle_end_space(skip_spaces(tmp[2]));
	if (!((strlen(vals[0]) < 3 || (strlen(vals[0]) == 3
					&& ft_strcmp(vals[0], "256") < 0)) && is_number(vals[0])))
		r = 0;
	if (!((strlen(vals[1]) < 3 || (strlen(vals[1]) == 3
					&& ft_strcmp(vals[1], "256") < 0)) && is_number(vals[1])))
		r = 0;
	if (!((strlen(vals[2]) < 3 || (strlen(vals[2]) == 3
					&& ft_strcmp(vals[2], "256") < 0)) && is_number(vals[2])))
		r = 0;
	free_char_array(tmp);
	return (r);
}
