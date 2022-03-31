/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:07:40 by selee             #+#    #+#             */
/*   Updated: 2021/06/22 12:19:55 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	new_len;

	i = 0;
	if (!s)
		return (NULL);
	new_len = ft_strlen(s);
	if (start >= new_len)
		new_len = 0;
	if (len < new_len)
		new_len = len;
	ptr = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!ptr)
		return (NULL);
	while (i < new_len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
