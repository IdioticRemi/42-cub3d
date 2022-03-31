/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:22:09 by selee             #+#    #+#             */
/*   Updated: 2020/12/03 14:59:04 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (NULL);
	while (((unsigned char *)s)[i] != (unsigned char)c && (i < n - 1))
		i++;
	if (((unsigned char *)s)[i] == (unsigned char)c)
		return (&((unsigned char *)s)[i]);
	return (NULL);
}
