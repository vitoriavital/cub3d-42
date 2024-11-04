/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:18:55 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 11:23:19 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	build_rgb(char **colors, int *rgb, char flag)
{
	if (flag == 'b')
	{
		rgb[0] = ft_atoi(colors[0]);
		rgb[1] = ft_atoi(colors[1]);
		rgb[2] = ft_atoi(colors[2]);
	}
	else if (flag == 'f')
	{
		free(colors[0]);
		free(colors[1]);
		free(colors[2]);
		free(colors);
	}
}
