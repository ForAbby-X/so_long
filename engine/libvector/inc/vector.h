/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:22 by alde-fre          #+#    #+#             */
/*   Updated: 2024/06/28 11:20:13 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# ifndef VECTOR_DEFAULT_SIZE
#  define VECTOR_DEFAULT_SIZE 64
# endif

//-Storage class for any types
typedef struct s_vector	t_vector;
//-Type for storing vector error
typedef enum e_error	t_error;
//-Type for storing vector length
typedef unsigned int	t_length;
typedef void			*t_object;
typedef t_object		(*t_copy_method)(
			void *dest, void *src, t_length const len);

void		*_vec_memcpy(void *dest, void *src, t_length const len);
void		_vec_memmov(void *dest, void *src, t_length len);

t_vector	vector_create(t_length const type_size);
void		vector_destroy(t_vector *const vector);
void		vector_set_copy_method(t_vector *const vector, t_copy_method cpy_m);
//BOTH VECTORS MUST BE INITIALISED BEFORE
t_vector	*vector_copy(t_vector *const vec_dest, t_vector *const vec_src);

t_error		vector_reserve(t_vector *const vector, t_length const len);
t_error		vector_resize(t_vector *const vector, t_length const len);
void		vector_clear(t_vector *const vector);
t_error		vector_shrink_to_fit(t_vector *const vector);

t_object	vector_addback(t_vector *const vector, t_object object);
t_object	vector_addfront(t_vector *const vector, t_object object);
t_object	vector_insert(
				t_vector *const vector,
				t_object object,
				t_length const index);
t_vector	*vector_insert_vector(
				t_vector *const vec_dest,
				t_vector const *const vec_src,
				t_length const index);

t_object	vector_pop(t_vector *const vector);
t_object	vector_erase(t_vector *const vector, t_length const index);

t_object	vector_get(t_vector const *const vector, t_length const index);
t_object	vector_buffer(t_vector const *const vector);
t_length	vector_size(t_vector const *const vector);
t_length	vector_capacity(t_vector const *const vector);
t_vector	vector_subvec(
				t_vector const *const vector,
				t_length const index,
				t_length const length);

t_length	vector_count_if(
				t_vector const *const vector,
				int (*cond)(t_object object));
void		vector_for_each(
				t_vector const *const vector,
				void (*func)(t_object object));

void		_vec_choose_method(t_vector *const vector);

t_object	_1byte_copy_method(void *dest, void *src, t_length const len);
t_object	_2byte_copy_method(void *dest, void *src, t_length const len);
t_object	_4byte_copy_method(void *dest, void *src, t_length const len);
t_object	_8byte_copy_method(void *dest, void *src, t_length const len);

enum e_error
{
	VEC_SUCCES = 0,
	VEC_FAILURE = 1,
	VEC_MEMORY_FAILURE = 2,
	VEC_OBJECT_TYPE_MISMATCH = 3
};

struct s_vector
{
	void			*data;
	t_length		size;
	t_length		capacity;
	void			*buffer;
	t_length		type_size;
	t_copy_method	copy_method;
};

#endif
