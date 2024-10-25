/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:35 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/25 13:28:08 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	draw_tile(t_game *game, t_mini *mini, int px, int py, uint32_t color)
{
	int			x;
	int			y;

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
			if (tile_y >= 0 && tile_y < game->map->height)
			{
				if (tile_x >= 0 && tile_x <= (int)ft_strlen(game->map->full_map[tile_y]))
				{
					if (game->map->full_map[tile_y][tile_x] > '0' && game->map->full_map[tile_y][tile_x] != '3')
						color = ft_pixel(100, 100, 100, 255);
					else if (game->map->full_map[tile_y][tile_x] == '0' || game->map->full_map[tile_y][tile_x] == '3')
						color = ft_pixel(0, 0, 0, 255);
					else
						color = ft_pixel(100, 100, 100, 255);

					draw_tile(game, mini, mini->offset + i * mini->tile, mini->offset + j * mini->tile, color);
				}
			}
		}
	}
}

static void	draw_background(t_game *game, t_mini *mini)
{
	int	i = mini->offset / 2;
	int	j = mini->offset / 2;

	while (i < mini->width + mini->offset)
	{
		j = mini->offset / 2;
		while (j < mini->height + mini->offset)
		{
			mlx_put_pixel(game->image, i, j, ft_pixel(100, 100, 100, 255));
			j++;
		}
		i++;
	}
}

void	ft_mini_map(void *param)
{
	t_game	*game;
	t_mini	*mini;

	game = (t_game *)param;
	mini = malloc(sizeof(t_mini));
	mini->offset = 20;
	mini->tile = 20;
	mini->width = SCREEN_WIDTH * 0.2;
	mini->height = SCREEN_HEIGHT * 0.2;
	mini->offset = 20;
	draw_background(game, mini);
	draw_walls_mm(game, mini);
	mini->px = ((mini->width - mini->offset) / 2) + mini->offset + mini->tile / 2;
	mini->py = ((mini->height - mini->offset) / 2) + mini->offset + mini->tile / 2;
	draw_tile(game, mini, mini->px, mini->py, ft_pixel(255, 0, 0, 255));
	// draw_player(game, mini);
	free(mini);
}
