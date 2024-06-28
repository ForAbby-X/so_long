/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:20:39 by alde-fre          #+#    #+#             */
/*   Updated: 2023/11/10 02:04:35 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_object	vector_addback(t_vector *const vector, t_object object)
{
	t_object	ret;

	if (vector->size + 1 > vector->capacity)
		if (vector_reserve(vector, vector->capacity + vector->capacity / 2))
			return (NULL);
	vector->copy_method(vector->data + vector->type_size * vector->size,
		object, vector->type_size);
	ret = vector->data + vector->type_size * vector->size;
	vector->size++;
	return (ret);
}

t_object	vector_addfront(t_vector *const vector, t_object object)
{
	if (vector->size + 1 > vector->capacity)
		if (vector_reserve(vector, vector->capacity + vector->capacity / 2))
			return (NULL);
	_vec_memmov(vector->data + vector->type_size, vector->data,
		vector->type_size * vector->size);
	vector->copy_method(vector->data, object, vector->type_size);
	vector->size++;
	return (vector->data);
}

t_object	vector_insert(
				t_vector *const vector,
				t_object object,
				t_length const index)
{
	if (vector->size + 1 > vector->capacity)
		if (vector_reserve(vector, vector->capacity + vector->capacity / 2))
			return (NULL);
	_vec_memmov(
		vector->data + vector->type_size * (index + 1),
		vector->data + vector->type_size * index,
		vector->type_size * (vector->size - index));
	vector->copy_method(vector->data + vector->type_size * index,
		object, vector->type_size);
	vector->size++;
	return (vector->data + vector->type_size * index);
}

t_vector	*vector_insert_vector(
				t_vector *const vec_dest,
				t_vector const *const vec_src,
				t_length const index)
{
	if (vec_dest->type_size != vec_src->type_size || index > vec_dest->size)
		return (NULL);
	if (!vec_src->size)
		return (vec_dest);
	if (vec_dest->size + vec_src->size > vec_dest->capacity)
		if (vector_reserve(vec_dest,
				vec_dest->capacity + vec_src->size + vec_dest->capacity / 2))
			return (NULL);
	_vec_memmov(
		vec_dest->data + vec_dest->type_size * (index + vec_src->size),
		vec_dest->data + vec_dest->type_size * index,
		vec_src->type_size * vec_src->size);
	_vec_memmov(
		vec_dest->data + vec_dest->type_size * index,
		vec_src->data,
		vec_src->type_size * vec_src->size);
	vec_dest->size += vec_src->size;
	return (vec_dest);
}
