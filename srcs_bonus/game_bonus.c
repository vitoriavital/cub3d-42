/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:13:16 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	game_loop(t_game *game)
{
	uint32_t	x;
	t_dda		*dda;

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
