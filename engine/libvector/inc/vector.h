/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:17:22 by alde-fre          #+#    #+#             */
/*   Updated: 2023/02/15 14:12:23 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# define NO_OBJ (0)
# define VEC_ERROR (NULL)

# include <stdlib.h>
# include <stdint.h>

/* TYPEDEF */
typedef struct s_vector	t_vector;
typedef unsigned int	t_length;
typedef void *			t_object;

/* FUNCTIONS */
/* fastest memcpy */
void		_ft_memcpy(void *dest, void *src, unsigned int len);
void		_ft_memmove(void *dest, void const *src, size_t len);
int			_ft_vector_resize(t_vector *vector, t_length len);

t_vector	*ft_vector_create(t_length base_size);
void		ft_vector_destroy(t_vector *vector);
t_object	ft_vector_add(t_vector *vector, t_object object);
t_object	ft_vector_pop(t_vector *vector);
t_length	ft_vector_size(t_vector *vector);

t_object	ft_vector_rem(t_vector *vector, t_length index);
t_object	ft_vector_add_front(t_vector *vector, t_object object);
void		ft_vector_swap(t_vector *vector, t_length i_a, t_length i_b);
t_object	ft_vector_get(t_vector *vector, t_length index);
t_length	ft_vector_countif(t_vector *vector, int (*cond)(t_object obj));

/* STRUCTURES */
struct s_vector
{
	t_object	*data;
	t_length	size;
	t_length	capacity;
	t_length	base_size;
};

#endif
