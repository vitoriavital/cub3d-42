/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darkmode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:38:17 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/22 16:37:03 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	apply_dark_filter(mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint8_t		*pixel;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			pixel = &texture->pixels[(y * texture->width + x) * 4];
			pixel[0] = (uint8_t)(pixel[0] * 0.5);
			pixel[1] = (uint8_t)(pixel[1] * 0.5);
			pixel[2] = (uint8_t)(pixel[2] * 0.5);
			x++;
		}
		y++;
	}
}
