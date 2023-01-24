/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:13:45 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:13:49 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_balek25(char *str, long i, long count)
{
	int	num;

	num = 0;
	while (count > 0 + num)
	{
		if (i < 0)
		{
			str[0] = '-';
			i = i * -1;
			num = 1;
		}
		else
		{
			count--;
			str[count] = ((i % 10) + '0');
			i /= 10;
		}
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	i;
	long	count;
	char	*str;

	i = n;
	count = 0;
	if (i < 0)
	{
		count++;
		i = i * -1;
	}
	if (i == 0)
		count++;
	while (i != 0)
	{
		i = i / 10;
		count++;
	}
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (0);
	i = n;
	str[count] = 0;
	ft_balek25(str, i, count);
	return (str);
}
