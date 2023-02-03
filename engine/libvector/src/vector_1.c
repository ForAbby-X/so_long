/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/03 15:57:00 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*ft_vector_create(t_length base_size)
{
	t_vector	*vector;

	vector = malloc(base_size * sizeof(t_vector));
	if (vector == NULL)
		return (NULL);
	vector->data = malloc(base_size * sizeof(t_object));
	if (vector->data == NULL)
		return (free(vector), NULL);
	vector->size = 0;
	vector->capacity = base_size;
	vector->base_size = base_size;
	return (vector);
}

void	ft_vector_destroy(t_vector *vector)
{
	free(vector->data);
	free(vector);
}

t_object	ft_vector_add(t_vector *vector, t_object object)
{
	if (vector->size >= vector->capacity)
	{
		if (_ft_vector_resize(vector, vector->capacity * 2))
			return (VEC_ERROR);
	}
	vector->data[vector->size] = object;
	vector->size++;
	return (object);
}

t_object	ft_vector_pop(t_vector *vector)
{
	t_object	object;

	if (vector->size == 0)
		return (NO_OBJ);
	vector->size--;
	object = vector->data[vector->size];
	return (object);
}

t_length	ft_vector_size(t_vector *vector)
{
	return (vector->size);
}
