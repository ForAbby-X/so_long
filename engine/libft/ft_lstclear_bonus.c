/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:14:05 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:14:07 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*test;
	t_list	*new;

	test = *lst;
	while (test)
	{
		new = test->next;
		ft_lstdelone(test, (*del));
		test = new;
	}
	*lst = 0;
}
