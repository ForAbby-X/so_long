/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:19:13 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:19:16 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int y)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)y)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (!y)
		return ((char *)&str[i]);
	return (NULL);
}
