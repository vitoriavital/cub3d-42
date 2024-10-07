/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:20:54 by mavitori          #+#    #+#             */
/*   Updated: 2024/09/18 13:25:11 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

t_vector	*ft_vector_create(float x, float y)
{
	t_vector	*v;

	v = malloc(sizeof(t_vector));
	v->x = x;
	v->y = y;
	return (v);
}

void	ft_vector_add(t_vector *v1, t_vector *v2, t_vector *result)
{
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
}

t_vector	*ft_vector_copy(t_vector *v)
{
	t_vector	*copy;

	copy = malloc(sizeof(t_vector));
	copy->x = v->x;
	copy->y = v->y;
	return (copy);
}

void	ft_vector_floor(t_vector *v, t_vector *result)
{
	result->x = floor(v->x);
	result->y = floor(v->y);
}

void	ft_vector_scalar(t_vector *v, double scalar, t_vector *result)
{
	result->x = v->x * scalar;
	result->y = v->y * scalar;
}
