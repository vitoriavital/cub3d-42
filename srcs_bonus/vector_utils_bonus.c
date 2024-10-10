/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:52:12 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/08 15:25:14 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

float	ft_vector_magnitude(t_vector *v)
{
	double	result;

	result = sqrt(v->x * v->x + v->y * v->y);
	return (result);
}

void	ft_vector_normalize(t_vector *v)
{
	float	length;

	length = sqrt(v->x * v->x + v->y * v->y);
	if (length > 0)
	{
		v->x /= length;
		v->y /= length;
	}
}

void	ft_vector_rotate(t_vector *v, float angle)
{
	float		radians;
	float		x;
	float		y;

	// Convert angle to radians
	radians = angle * PI / 180.0;
	// Apply rotation formula
	x = v->x * cosf(radians) - v->y * sinf(radians);
	y = v->x * sinf(radians) + v->y * cosf(radians);
	v->x = x;
	v->y = y;
}
