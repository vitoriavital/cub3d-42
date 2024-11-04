/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dark_mode_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:07:11 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/11/02 15:39:38 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

void	init_particles(t_particle *particles, int count, uint32_t color)
{
	int	i;

	i = 0;
	while (i < count)
	{
		particles[i].x = rand() % SCREEN_WIDTH;
		particles[i].y = rand() % 500;
		particles[i].speed = (float)(rand() % 100) / 100.0 + 0.5;
		particles[i].size = rand() % 3 + 3;
		particles[i].color = color | ((rand() % 50) << 24);
		i++;
	}
}

void	update_particles(t_particle *particles, int count, uint32_t color)
{
	int	i;

	i = 0;
	while (i < count)
	{
		particles[i].y += particles[i].speed;
		if (particles[i].y >= SCREEN_HEIGHT)
		{
			particles[i].x = rand() % SCREEN_WIDTH;
			particles[i].y = 0;
			particles[i].speed = (float)(rand() % 100) / 100.0 + 0.5;
			particles[i].color = color;
		}
		i++;
	}
}

void	draw_particles(t_game *game, t_particle *particles, int count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < particles[i].size)
		{
			k = 0;
			while (k < particles[i].size)
			{
				if ((int)particles[i].x + j < SCREEN_WIDTH
					&& (int)particles[i].y + k < SCREEN_HEIGHT)
					mlx_put_pixel(game->image, (int)particles[i].x + j, \
					(int)particles[i].y + k, particles[i].color);
				k++;
			}
			j++;
		}
		i++;
	}
}

void	apply_dark_filter(mlx_texture_t *texture)
{
	int		x;
	int		y;
	uint8_t	*pixel;

	y = 0;
	while (y < (int)texture->height)
	{
		x = 0;
		while (x < (int)texture->width)
		{
			pixel = &texture->pixels[(y * texture->width + x) * 4];
			pixel[0] = (uint8_t)(pixel[0] * 1);
			pixel[1] = (uint8_t)(pixel[1] * 0.1);
			pixel[2] = (uint8_t)(pixel[2] * 0.1);
			x++;
		}
		y++;
	}
}
