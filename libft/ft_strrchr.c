/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 16:37:42 by selee             #+#    #+#             */
/*   Updated: 2020/12/01 12:03:16 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	size_t	i;

	ptr = (char *)s;
	i = 0;
	while (s[i])
		i++;
	if (c == '\0')
		return (ptr + i);
	while (i > 0)
	{
		i--;
		if (ptr[i] == (unsigned char)c)
			return (ptr + i);
	}
	return (NULL);
}
