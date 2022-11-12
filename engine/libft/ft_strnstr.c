/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:47 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:20:52 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*str2 == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] && str2[j]
			&& i + j < len && str[i + j] == str2[j])
		j++;
		if (j == ft_strlen(str2))
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
