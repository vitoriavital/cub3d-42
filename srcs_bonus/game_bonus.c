/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/26 14:44:57 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	game_loop(t_game *game)
{
	uint32_t	x;
	t_dda		*dda;
	static t_particle particles[100];
	static int initialized = 0;
	if (!initialized)
	{
		init_particles(particles, 100, 0xFFFFFFFF);
		game->particle_color = 0xFFFFFFFF;
		initialized = 1;
	}
	update_particles(particles, 100, game->particle_color);
	x = 0;
	dda = malloc(sizeof(t_dda));
	while (x < SCREEN_WIDTH)
	{
		game->current_pixel = x;
		dda->multiplier = 2 * (x / (float)SCREEN_WIDTH) - 1;
		ft_vector_scalar(game->plane, dda->multiplier, game->camera_pixel);
		ft_vector_add(game->dir, game->camera_pixel, game->ray_dir);
		delta_dist(game, dda);
		ft_vector_floor(game->pos, game->map_pos);
		dist_to_side(game, dda);
		build_ray(game, dda);
		draw_particles(game, particles, 100);
		x++;
	}
	free(dda);
}

void	ft_game(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_floor(game);
	draw_ceiling(game);
	game_loop(game);
}
