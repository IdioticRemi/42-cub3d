/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 13:22:41 by selee             #+#    #+#             */
/*   Updated: 2021/05/03 13:00:12 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_node *lst)
{
	int		count;
	t_node	*temp;

	count = 0;
	temp = lst;
	if (lst != 0)
	{
		while ((*temp).next != NULL)
		{
			count++;
			temp = (*temp).next;
		}
		if ((*temp).next == NULL)
			count++;
	}
	return (count);
}
