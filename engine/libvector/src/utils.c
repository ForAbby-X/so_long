/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:35 by alde-fre          #+#    #+#             */
/*   Updated: 2023/01/24 15:45:45 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	_ft_memcpy(void *dest, void *src, unsigned int len)
{
	void	*ptr;

	ptr = src + len;
	while (src < ptr - 8)
	{
		*((uint64_t *)dest) = *((uint64_t *)src);
		src += 8;
		dest += 8;
	}
	while (src < ptr - 4)
	{
		*((uint32_t *)dest) = *((uint32_t *)src);
		src += 4;
		dest += 4;
	}
	while (src < ptr - 2)
	{
		*((uint16_t *)dest) = *((uint16_t *)src);
		src += 2;
		dest += 2;
	}
	while (src < ptr)
		*(uint8_t *)dest++ = *(uint8_t *)src++;
}

void	_ft_memmove(void *dest, void const *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	i = 0;
	if (str2 < str1)
		while (++i <= len)
			*(str1 + len - i) = *(str2 + len - i);
	else
		while (len-- > 0)
			*(str1++) = *(str2++);
}

int	_ft_vector_resize(t_vector	*vector, t_length len)
{
	t_object	*data;

	data = malloc(len * sizeof(t_object));
	if (data == NULL)
		return (1);
	if (len > vector->capacity)
		_ft_memcpy(data, vector->data, vector->capacity * sizeof(t_object));
	else
		_ft_memcpy(data, vector->data, len * sizeof(t_object));
	free(vector->data);
	vector->capacity = len;
	vector->data = data;
	return (0);
}
