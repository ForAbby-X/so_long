/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:35 by alde-fre          #+#    #+#             */
/*   Updated: 2023/11/10 01:57:38 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	*_vec_memcpy(void *dest, void *src, t_length const len)
{
	void		*ptr;
	void *const	start = dest;

	ptr = src + len;
	while (src <= ptr - 8)
	{
		*((uint64_t *)dest) = *((uint64_t *)src);
		src += 8;
		dest += 8;
	}
	if (src <= ptr - 4)
	{
		*((uint32_t *)dest) = *((uint32_t *)src);
		src += 4;
		dest += 4;
	}
	if (src <= ptr - 2)
	{
		*((uint16_t *)dest) = *((uint16_t *)src);
		src += 2;
		dest += 2;
	}
	if (src < ptr)
		*(uint8_t *)dest++ = *(uint8_t *)src++;
	return (start);
}

void	_vec_memmov(void *dest, void *src, t_length const len)
{
	void	*ptr;

	if (dest == src)
		return ;
	if (dest < src || dest >= src + len)
		return ((void)_vec_memcpy(dest, src, len));
	ptr = src + len - 1;
	dest += len - 1;
	while (ptr >= src)
		*(uint8_t *)dest-- = *(uint8_t *)ptr--;
}
