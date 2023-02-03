/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:20:39 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/03 15:50:23 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_object	ft_vector_rem(t_vector *vector, t_length index)
{
	t_object	object;

	if (vector->size == 0 || index >= vector->size)
		return (NO_OBJ);
	object = vector->data[index];
	_ft_memmove(&vector->data[index], &vector->data[index + 1],
		(vector->size - (index + 1)) * sizeof(t_object));
	vector->size--;
	return (object);
}

t_object	ft_vector_add_front(t_vector *vector, t_object object)
{
	if (vector->size >= vector->capacity)
		if (_ft_vector_resize(vector, vector->capacity * 2))
			return (VEC_ERROR);
	_ft_memmove(vector->data + sizeof(t_object), vector->data, vector->size
		* sizeof(t_object));
	vector->data[0] = object;
	vector->size++;
	return (vector->data);
}

void	ft_vector_swap(t_vector *vector, t_length i_a, t_length i_b)
{
	t_object	obj;

	obj = vector->data[i_a];
	vector->data[i_a] = vector->data[i_b];
	vector->data[i_b] = obj;
}

t_object	ft_vector_get(t_vector *vector, t_length index)
{
	if (index >= vector->size)
		return (NO_OBJ);
	return (vector->data[index]);
}

t_length	ft_vector_countif(t_vector *vector, int (*cond)(t_object obj))
{
	t_length	i;
	t_length	count;

	i = 0;
	count = 0;
	while (i < ft_vector_size(vector))
	{
		if (cond(ft_vector_get(vector, i)) == 0)
			count++;
		i++;
	}
	return (count);
}
