/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darkmode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:38:17 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/13 19:51:44 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	apply_dark_filter(mlx_texture_t *texture)
{
	int x;
	int y;
	uint8_t *pixel;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			pixel = &texture->pixels[(y * texture->width + x) * 4];
			pixel[0] = (uint8_t)(pixel[0] * 0.5);  // Red
			pixel[1] = (uint8_t)(pixel[1] * 0.5);  // Green
			pixel[2] = (uint8_t)(pixel[2] * 0.5);  // Blue
			x++;
		}
		y++;
	}
}


