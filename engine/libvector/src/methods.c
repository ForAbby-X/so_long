/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   methods.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:10:33 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/17 17:35:42 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_object	_1byte_copy_method(void *dest, void *src, t_length const len)
{
	(void)len;
	*(uint8_t *)dest = *(uint8_t *)src;
	return (dest);
}

t_object	_2byte_copy_method(void *dest, void *src, t_length const len)
{
	(void)len;
	*(uint16_t *)dest = *(uint16_t *)src;
	return (dest);
}

t_object	_4byte_copy_method(void *dest, void *src, t_length const len)
{
	(void)len;
	*(uint32_t *)dest = *(uint32_t *)src;
	return (dest);
}

t_object	_8byte_copy_method(void *dest, void *src, t_length const len)
{
	(void)len;
	*(uint64_t *)dest = *(uint64_t *)src;
	return (dest);
}

t_object	_large_copy_method(void *dest, void *src, t_length const len)
{
	_vec_memcpy(dest, src, len);
	return (dest);
}
