/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:37:26 by seoyounglee       #+#    #+#             */
/*   Updated: 2021/05/03 13:03:06 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	i;
	size_t	len_all;

	if (!s1 && !s2)
		return (NULL);
	len_all = (ft_strlen(s1) + ft_strlen(s2) + 1);
	dst = (char *)malloc(sizeof(char) * len_all);
	if (!dst)
		return (NULL);
	i = 0;
	len_all = 0;
	if (s1)
	{
		while (s1[i])
			dst[len_all++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			dst[len_all++] = s2[i++];
	}
	dst[len_all] = '\0';
	return (dst);
}
