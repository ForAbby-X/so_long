/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:55 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:20:58 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int y)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == (char)y)
			return ((char *)&str[i]);
		i--;
	}
	if (str[0] == (char)y)
		return ((char *)&str[0]);
	return (NULL);
}
