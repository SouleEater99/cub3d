/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:23:14 by ael-maim          #+#    #+#             */
/*   Updated: 2023/11/11 15:33:16 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*to_free;

	if (lst && del)
	{
		to_free = *lst;
		while (to_free)
		{
			tmp = to_free->next;
			del(to_free->content);
			free(to_free);
			to_free = tmp;
		}
		*lst = NULL;
	}
}
