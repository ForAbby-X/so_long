/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_modifiers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:25:21 by alde-fre          #+#    #+#             */
/*   Updated: 2023/10/13 11:14:24 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_error	vector_reserve(t_vector *const vector, t_length const len)
{
	void	*data;

	if (len > vector->capacity)
	{
		data = malloc(vector->type_size * len);
		if (data == NULL)
			return (VEC_MEMORY_FAILURE);
		_vec_memcpy(data, vector->data, vector->type_size * vector->size);
		free(vector->data);
		vector->data = data;
		vector->capacity = len;
	}
	return (VEC_SUCCES);
}

t_error	vector_resize(t_vector	*vector, t_length const len)
{
	t_error const	error = vector_reserve(vector, len);

	if (error)
		return (error);
	vector->size = len;
	return (VEC_SUCCES);
}

void	vector_clear(t_vector *const vector)
{
	vector->size = 0;
}

t_error	vector_shrink_to_fit(t_vector *const vector)
{
	void	*data;

	if (vector->size == vector->capacity)
		return (VEC_FAILURE);
	data = malloc(vector->type_size * vector->size);
	if (data == NULL)
		return (VEC_MEMORY_FAILURE);
	_vec_memcpy(data, vector->data, vector->type_size * vector->size);
	free(vector->data);
	vector->data = data;
	vector->capacity = vector->size;
	return (VEC_SUCCES);
}
