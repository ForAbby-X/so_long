/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:18:49 by alde-fre          #+#    #+#             */
/*   Updated: 2022/09/21 20:18:52 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	test;

	if (n < 0)
	{
		test = n * -1;
		ft_putchar_fd('-', fd);
	}
	else
		test = n;
	if (test > 9)
		ft_putnbr_fd(test / 10, fd);
	ft_putchar_fd('0' + (test % 10), fd);
}
