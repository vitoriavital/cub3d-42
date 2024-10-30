/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:55:42 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 12:15:19 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	check_wall(t_game *game, float x, float y)
{
	int	row;
	int	column;

	row = (int)y;
	column = (int)x;
	if (game->map->full_map[row][column] == '0'
		|| game->map->full_map[row][column] == '3')
		return (0);
	else
		return (-1);
}

static void	update_position(t_game *game, float delta_x, float delta_y)
{
	float	future_x;
	float	future_y;

	future_x = game->pos->x + delta_x;
	future_y = game->pos->y + delta_y;
	if (check_wall(game, future_x, future_y) != -1)
	{
		game->pos->y += delta_y;
		game->pos->x += delta_x;
	}
}

void	move_player_up_down(t_game *game, int key, int multiplier)
{
	float	move_x;
	float	move_y;

	move_x = 0.0;
	move_y = 0.0;
	if (multiplier != 1)
	{
		update_position(game, 0, multiplier);
		return ;
	}
	if (key == MLX_KEY_W)
	{
		move_x += game->dir->x * 0.05 * multiplier;
		move_y += game->dir->y * 0.05 * multiplier;
		update_position(game, move_x, move_y);
	}
	if (key == MLX_KEY_S)
	{
		move_x -= game->dir->x * 0.05 * multiplier;
		move_y -= game->dir->y * 0.05 * multiplier;
		update_position(game, move_x, move_y);
	}
}

void	move_player_left_right(t_game *game, int key, int multiplier)
{
	float		move_x;
	float		move_y;
	t_vector	*v;

	move_x = 0.0;
	move_y = 0.0;
	if (multiplier != 1)
	{
		update_position(game, multiplier, 0);
		return ;
	}
	if (key == MLX_KEY_A)
		v = ft_vector_create(game->dir->y, -game->dir->x);
	else
		v = ft_vector_create(-game->dir->y, game->dir->x);
	ft_vector_normalize(v);
	move_x += v->x * 0.05;
	move_y += v->y * 0.05;
	free (v);
	if (key == MLX_KEY_A)
		update_position(game, move_x, move_y);
	else
		update_position(game, move_x, move_y);
}
