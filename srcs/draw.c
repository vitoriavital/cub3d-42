/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by mavitori          #+#    #+#             */
/*   Updated: 2024/09/20 16:46:20 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_floor(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			color = ft_pixel(190, 190, 255, 255);
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_ceiling(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			color = ft_pixel(105, 105, 105, 255);
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_wall(t_game *game, float dist, t_dda *dda)
{
	t_wall	*wall;

	wall = malloc(sizeof(t_wall));
	wall->height = SCREEN_HEIGHT / dist;
	wall->start = SCREEN_HEIGHT / 2 - wall->height / 2;
	wall->end = SCREEN_HEIGHT / 2 + wall->height / 2;
	if (wall->start < 0 || dist == 0)
		wall->start = 0;
	if (wall->end >= SCREEN_HEIGHT || dist == 0)
		wall->end = SCREEN_HEIGHT - 1;
	draw_wall_line(wall, dda, game);
	free(wall);
}
