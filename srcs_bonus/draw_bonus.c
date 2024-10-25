/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/25 15:15:28 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static uint32_t	texture_bonus(uint32_t x, uint32_t y, t_game *game, char side)
{
	uint32_t	tex_x;
	uint32_t	tex_y;
	uint32_t	tex_width;
	uint32_t	tex_height;
	uint8_t		*color;

	tex_width = game->ceiling->width;
	tex_height = game->ceiling->height;
	if (side == 'c')
	{
		tex_x = (x * tex_width) / SCREEN_WIDTH;
		tex_y = (y * tex_height) / (SCREEN_HEIGHT / 2);
		color = &game->ceiling->pixels[(tex_y * tex_width + tex_x) \
		* game->ceiling->bytes_per_pixel];
	}
	else
	{
		tex_width = game->floor->width;
		tex_height = game->floor->height;
		tex_x = (x * tex_width) / SCREEN_WIDTH;
		tex_y = ((y - SCREEN_HEIGHT / 2) * tex_height) / (SCREEN_HEIGHT / 2);
		color = &game->floor->pixels[(tex_y * tex_width + tex_x) \
		* game->floor->bytes_per_pixel];
	}

	return (ft_pixel(color[0], color[1], color[2], color[3]));
}

void	draw_ceiling(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	int			rgb[3];
	char		**colors;

	x = 0;
	colors = ft_split(game->map->ceiling_color, ',');
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			if (game->bonus_textures == 0)
				color = ft_pixel(rgb[0], rgb[1], rgb[2], 255);
			else
				color = texture_bonus(x, y, game, 'c');
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
}

void	draw_floor(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	int			rgb[3];
	char		**colors;

	x = 0;
	colors = ft_split(game->map->floor_color, ',');
	rgb[0] = ft_atoi(colors[0]);
	rgb[1] = ft_atoi(colors[1]);
	rgb[2] = ft_atoi(colors[2]);
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			if (game->bonus_textures == 0)
				color = ft_pixel(rgb[0], rgb[1], rgb[2], 255);
			else
				color = texture_bonus(x, y, game, 'f');
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
	free(colors[0]);
	free(colors[1]);
	free(colors[2]);
	free(colors);
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
