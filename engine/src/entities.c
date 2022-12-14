/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 02:10:34 by alde-fre          #+#    #+#             */
/*   Updated: 2022/11/28 18:50:32 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_entity	*ft_ent_add(t_data *game, t_entity *ent)
{
	if (ent == NULL)
		return (NULL);
	ft_vector_add(game->map.entities, ent);
	return (ent);
}

t_entity	*ft_ent_get(t_data *game, t_length index)
{
	return (ft_vector_get(game->map.entities, index));
}
