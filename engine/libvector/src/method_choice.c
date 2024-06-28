/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method_choice.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:40:34 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/17 17:36:46 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	_vec_choose_method(t_vector *const vector)
{
	if (vector->type_size == 1)
		vector->copy_method = &_1byte_copy_method;
	else if (vector->type_size == 2)
		vector->copy_method = &_2byte_copy_method;
	else if (vector->type_size == 4)
		vector->copy_method = &_4byte_copy_method;
	else if (vector->type_size == 8)
		vector->copy_method = &_8byte_copy_method;
	else
		vector->copy_method = &_vec_memcpy;
}

void	vector_set_copy_method(t_vector *const vector, t_copy_method cpy_m)
{
	if (cpy_m == NULL)
		_vec_choose_method(vector);
	else
		vector->copy_method = cpy_m;
}
