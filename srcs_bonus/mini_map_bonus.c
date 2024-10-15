/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:26:15 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/15 17:43:12 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	draw_tile(t_game *game, t_mini *mini, int px, int py, uint32_t color)
{
	int			x;
	int			y;
	int			width;

	x = 0;
	while (x < mini->tile)
	{
		y = 0;
		while (y < mini->tile)
		{
			mlx_put_pixel(game->image, px - 4 + x, py - 4 + y, color);
			y++;
		}
		x++;
	}
}

static void	draw_walls_mm(t_game *game, t_mini *mini)
{
	int			i;
	int			j;
	int			map_x;
	int			map_y;
	int			tile_x;
	int			tile_y;
	uint32_t	color;

	map_x = (int)game->map_pos->x;
	map_y = (int)game->map_pos->y;

	int tiles_wide = mini->width / mini->tile;
	int tiles_high = mini->height / mini->tile;

	for (i = 0; i < tiles_wide; i++)
	{
		for (j = 0; j < tiles_high; j++)
		{
			tile_x = map_x - (tiles_wide / 2) + i;
			tile_y = map_y - (tiles_high / 2) + j;

			if (tile_x >= 0 && tile_x < 10 && tile_y >= 0 && tile_y < 10)
			{
				if (game->map->full_map[tile_y][tile_x] > '0' && game->map->full_map[tile_y][tile_x] != '3')
					color = ft_pixel(255, 255, 255, 255);
				else
					color = ft_pixel(0, 0, 0, 255);

				draw_tile(game, mini, mini->offset + i * mini->tile, mini->offset + j * mini->tile, color);
			}
		}
	}
}

// static void	draw_player(t_game *game, t_mini *mini)
// {
// 	int			x;
// 	int			y;
// 	int			radius;
// 	uint32_t	color;

// 	color = ft_pixel(255, 0, 0, 255);
// 	radius = mini->tile / 2.5;

// 	y = -radius;
// 	while (y <= radius)
// 	{
// 		x = -radius;
// 		while (x <= radius)
// 		{
// 			// Only draw pixels inside the circle using Pythagoras theorem
// 			if (x * x + y * y <= radius * radius)
// 			{
// 				mlx_put_pixel(game->image, mini->px + x, mini->py + y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	ft_mini_map(void *param)
{
	t_game	*game;
	uint32_t	color;
	t_mini	*mini;

	game = (t_game *)param;
	mini = malloc(sizeof(t_mini));
	mini->offset = 20;
	mini->tile = 20;
	mini->width = SCREEN_WIDTH * 0.2;
	mini->height = SCREEN_HEIGHT * 0.2;
	mini->offset = 20;
	int	i = mini->offset;
	int	j = mini->offset;
	draw_walls_mm(game, mini);
	mini->px = ((mini->width - mini->offset) / 2) + mini->offset + 10;
	mini->py = ((mini->height - mini->offset) / 2) + mini->offset + 10;
	draw_tile(game, mini, mini->px, mini->py, ft_pixel(255, 0, 0, 255));
	// draw_player(game, mini);

}
