/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selee <selee@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 19:18:57 by selee             #+#    #+#             */
/*   Updated: 2020/12/14 10:32:16 by selee            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_node **lst, void (*del)(int))
{
	t_node	*curr_elem;
	t_node	*next_elem;

	if (!lst || !del)
		return ;
	curr_elem = *lst;
	while (curr_elem)
	{
		next_elem = (*curr_elem).next;
		ft_lstdelone(curr_elem, del);
		curr_elem = next_elem;
	}
	*lst = NULL;
}
