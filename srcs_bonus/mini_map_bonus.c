/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:26:15 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/10 09:45:23 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	draw_pixels(t_game *game, uint32_t color, float px, float py)
{
	int			x;
	int			y;
	int			offset;
	int			width;

	x = 0;
	y = 0;
	offset = 20;
	width = 10;
	while (x < width)
	{
		y = 0;
		while (y < width)
		{
			mlx_put_pixel(game->image, px * width + offset + x, py * width + offset + y, color);
			y++;
		}
		x++;
	}
}

void	ft_mini_map(void *param)
{
	t_game	*game;
	uint32_t	color;
	int		offset;

	offset = 20;
	game = (t_game *)param;
	int	i = 0;
	int	j = 0;

	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			if (game->map->full_map[i][j] == '1')
				color = ft_pixel(255, 255, 0, 255);
			else
				color = ft_pixel(0, 0, 0, 255);
			draw_pixels(game, color, j, i);
			j++;
		}
		i++;
	}
	draw_pixels(game, ft_pixel(255, 0, 0, 255), game->pos->x, game->pos->y);
}
