/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/06/16 11:09:33 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector_create(t_length const type_size)
{
	t_vector	vector;

	if (type_size == 0)
		return ((t_vector){0});
	vector.data = malloc(type_size * VECTOR_DEFAULT_SIZE);
	if (vector.data == NULL)
		return ((t_vector){0});
	vector.buffer = malloc(type_size);
	if (vector.buffer == NULL)
		return (free(vector.data), (t_vector){0});
	vector.size = 0u;
	vector.capacity = VECTOR_DEFAULT_SIZE;
	vector.type_size = type_size;
	_vec_choose_method(&vector);
	return (vector);
}

void	vector_destroy(t_vector *const vector)
{
	free(vector->data);
	free(vector->buffer);
	vector->size = 0u;
}

t_vector	*vector_copy(t_vector *const vec_dest, t_vector *const vec_src)
{
	if (vec_dest == vec_src)
		return (NULL);
	vec_dest->type_size = vec_src->type_size;
	vector_reserve(vec_dest, vec_src->capacity);
	_vec_memcpy(vec_dest->data, vec_src->data,
		vec_src->type_size * vec_src->size);
	vec_dest->size = vec_src->size;
	vec_dest->copy_method = vec_src->copy_method;
	return (vec_dest);
}
