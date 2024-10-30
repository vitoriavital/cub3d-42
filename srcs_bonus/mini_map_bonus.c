/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:35 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 11:13:08 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	draw_tile(t_game *game, int px, int py, uint32_t color)
{
	int			x;
	int			y;

	x = 0;
	while (x < game->mini->tile)
	{
		y = 0;
		while (y < game->mini->tile)
		{
			mlx_put_pixel(game->image, px - 4 + x, py - 4 + y, color);
			y++;
		}
		x++;
	}
}

static void	calculate_walls(t_game *game, t_mini *mini, int i, int j)
{
	int			tile_x;
	int			tile_y;
	uint32_t	color;

	tile_x = (int)game->map_pos->x - (mini->width / mini->tile / 2) + i;
	tile_y = (int)game->map_pos->y - (mini->height / mini->tile / 2) + j;
	color = 0;
	if (tile_y >= 0 && tile_y < game->map->height)
	{
		if (tile_x >= 0
			&& tile_x <= (int)ft_strlen(game->map->full_map[tile_y]))
		{
			if (game->map->full_map[tile_y][tile_x] > '0'
				&& game->map->full_map[tile_y][tile_x] != '3')
				color = mini->background_color;
			else if (game->map->full_map[tile_y][tile_x] == '0'
				|| game->map->full_map[tile_y][tile_x] == '3')
				color = mini->path_color;
			else
				color = mini->background_color;
			draw_tile(game, mini->offset + i * mini->tile,
				mini->offset + j * mini->tile, color);
		}
	}
}

static void	draw_walls_mini_map(t_game *game)
{
	int			i;
	int			j;
	int			tiles_width;
	int			tiles_height;

	tiles_height = game->mini->height / game->mini->tile;
	tiles_width = game->mini->width / game->mini->tile;
	i = 0;
	while (i < tiles_width)
	{
		j = 0;
		while (j < tiles_height)
		{
			calculate_walls(game, game->mini, i, j);
			j++;
		}
		i++;
	}
}

static void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = game->mini->offset - 4;
	j = game->mini->offset - 4;
	if (game->particle_color == 0x00000000)
	{
		game->mini->background_color = ft_pixel(100, 100, 100, 255);
		game->mini->path_color = ft_pixel(0, 0, 0, 255);
	}
	else
	{
		game->mini->background_color = ft_pixel(231, 219, 199, 255);
		game->mini->path_color = ft_pixel(173, 185, 91, 255);
	}
	while (i < game->mini->width + game->mini->offset - 4)
	{
		j = game->mini->offset - 4;
		while (j < game->mini->height + game->mini->offset - 4)
		{
			mlx_put_pixel(game->image, i, j, game->mini->background_color);
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
	game->mini = mini;
	draw_background(game);
	draw_walls_mini_map(game);
	mini->px = ((mini->width - mini->offset) / 2)
		+ mini->offset + mini->tile / 2;
	mini->py = ((mini->height - mini->offset) / 2)
		+ mini->offset + mini->tile / 2;
	draw_tile(game, mini->px, mini->py, ft_pixel(255, 0, 0, 255));
	free(mini);
}
