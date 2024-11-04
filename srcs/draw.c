/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:29:05 by mavitori          #+#    #+#             */
/*   Updated: 2024/11/04 15:18:48 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	build_rgb(char **colors, int *rgb, char flag)
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

void	draw_floor(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	int			rgb[3];
	char		**colors;

	x = 0;
	colors = ft_split(game->map->ceiling_color, ',');
	build_rgb(colors, rgb, 'b');
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT / 2)
		{
			color = ft_pixel(rgb[0], rgb[1], rgb[2], 255);
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
	build_rgb(colors, rgb, 'f');
}

void	draw_ceiling(t_game *game)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;
	int			rgb[3];
	char		**colors;

	x = 0;
	colors = ft_split(game->map->floor_color, ',');
	build_rgb(colors, rgb, 'b');
	while (x < SCREEN_WIDTH)
	{
		y = SCREEN_HEIGHT / 2;
		while (y < SCREEN_HEIGHT)
		{
			color = ft_pixel(rgb[0], rgb[1], rgb[2], 255);
			mlx_put_pixel(game->image, x, y, color);
			y++;
		}
		x++;
	}
	build_rgb(colors, rgb, 'f');
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
