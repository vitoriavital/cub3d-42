/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:52:28 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/08 15:23:52 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	calc_wall_dist(t_game *game, t_vector *wall_pos, t_dda *dda)
{
	float	player_dist_wall;
	float	dividend;
	//Calcular a distância do player até a parede
	if (dda->hit_side == 1)
	{
		//y ganhou = parede horizontal
		dda->player_dist_wall = dda->tmp_dda_y - dda->delta_dist_y;
	}
	else
	{
		//x ganhou = parede vertical
		dda->player_dist_wall = dda->tmp_dda_x - dda->delta_dist_x;
	}
	draw_wall(game, dda->player_dist_wall, dda);
}

static void	hit_wall(t_vector *wall_pos, t_dda *dda)
{
	if (dda->tmp_dda_x < dda->tmp_dda_y)
	{
		wall_pos->x += dda->step_x;
		dda->tmp_dda_x += dda->delta_dist_x;
		dda->hit_side = 0;
	}
	else
	{
		wall_pos->y += dda->step_y;
		dda->tmp_dda_y += dda->delta_dist_y;
		dda->hit_side = 1;
	}
}

void	build_ray(t_game *game, t_dda *dda)
{
	int			hit;
	t_vector	*wall_pos;
	int			x;
	int			y;
	// Calcular raios e desenhar altura das linhas
	// Algoritmo DDA(Digital Differential Analyzer)
	// Distância do player para a parede
	// 1. achar qual quadrado que tem parede naquela direção
	// 2. qual a distancia da parede
	hit = 0;
	dda->tmp_dda_x = dda->dist_to_side_x;
	dda->tmp_dda_y = dda->dist_to_side_y;
	wall_pos = ft_vector_copy(game->map_pos);
	while (hit == 0)
	{
		hit_wall(wall_pos, dda);
		x = (int)wall_pos->x;
		y = (int)wall_pos->y;
		if (game->map->full_map[y][x] > '0')
			hit = 1;
	}
	calc_wall_dist(game, wall_pos, dda);
	free(wall_pos);
}

void	dist_to_side(t_game *game, t_dda *dda)
{
	if (game->ray_dir->x < 0)
	{
		dda->dist_to_side_x = (game->pos->x - game->map_pos->x) \
			* dda->delta_dist_x;
		dda->step_x = -1;
	}
	else
	{
		dda->dist_to_side_x = (game->map_pos->x + 1.0 - game->pos->x) \
			* dda->delta_dist_x;
		dda->step_x = 1;
	}
	if (game->ray_dir->y < 0)
	{
		dda->dist_to_side_y = (game->pos->y - game->map_pos->y) \
			* dda->delta_dist_y;
		dda->step_y = -1;
	}
	else
	{
		dda->dist_to_side_y = (game->map_pos->y + 1.0 - game->pos->y) \
			* dda->delta_dist_y;
		dda->step_y = 1;
	}
	dda->hit_side = 0;
}

void	delta_dist(t_game *game, t_dda *dda)
{
	if (game->ray_dir->x == 0)
		dda->delta_dist_x = HUGE_VALF;
	else
	{
		if (game->ray_dir->y != 0)
			dda->delta_dist_x = fabsf(1 / game->ray_dir->x);
	}
	if (game->ray_dir->y == 0)
		dda->delta_dist_y = HUGE_VALF;
	else
	{
		if (game->ray_dir->x != 0)
			dda->delta_dist_y = fabsf(1 / game->ray_dir->y);
	}
}
