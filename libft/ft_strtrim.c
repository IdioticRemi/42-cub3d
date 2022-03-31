/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:53:31 by selee             #+#    #+#             */
/*   Updated: 2021/05/03 13:08:43 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_in_set(char chr, char const *set)
{
	size_t	index;

	index = 0;
	if (!set || !chr)
		return (0);
	while (set[index])
	{
		if (chr == set[index])
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	index;
	size_t	len;
	size_t	j;
	size_t	new_index;

	if (!s1 || !set)
		return (NULL);
	index = 0;
	new_index = 0;
	len = ft_strlen(s1);
	j = len;
	while (ft_is_in_set(s1[index], set))
		index++;
	while (j >= index && ft_is_in_set(s1[j - 1], set))
		j--;
	new_str = (char *)malloc(sizeof(char) * (j - index + 1));
	if (!new_str)
		return (NULL);
	while (index < j)
		new_str[new_index++] = s1[index++];
	new_str[new_index] = '\0';
	return (new_str);
}
