/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:51:27 by mavitori          #+#    #+#             */
/*   Updated: 2024/09/18 14:18:49 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

static int	check_wall(t_game *game, float x, float y, int dir)
{
	int	row;
	int	column;

	row = (int)y;
	column = (int)x;
	if (row < 0 || row >= MAP_HEIGHT || column < 0 || column >= MAP_WIDTH)
		return (-1);
	if (game->map->full_map[row][column] == '0')
		return (0);
	else
		return (-1);
}

static void	update_position(t_game *game, float delta_x,
		float delta_y, int direction)
{
	float	future_x;
	float	future_y;

	future_x = game->pos->x + delta_x;
	future_y = game->pos->y + delta_y;
	if (check_wall(game, future_x, future_y, direction) != -1)
	{
		game->pos->y += delta_y;
		game->pos->x += delta_x;
	}
}

static void	move_player_up_down(t_game *game, int key)
{
	float	move_x;
	float	move_y;

	move_x = 0.0;
	move_y = 0.0;
	if (key == MLX_KEY_W)
	{
		move_x += game->dir->x * 0.05;
		move_y += game->dir->y * 0.05;
		update_position(game, move_x, move_y, UP);
	}
	if (key == MLX_KEY_S)
	{
		move_x -= game->dir->x * 0.05;
		move_y -= game->dir->y * 0.05;
		update_position(game, move_x, move_y, DOWN);
	}
}

static void	move_player_left_right(t_game *game, int key)
{
	float		move_x;
	float		move_y;
	t_vector	*v;

	move_x = 0.0;
	move_y = 0.0;
	// Compute a perpendicular vector for walking right or left
	if (key == MLX_KEY_A)
		v = ft_vector_create(game->dir->y, -game->dir->x);
	else
		v = ft_vector_create(-game->dir->y, game->dir->x);
	ft_vector_normalize(v);
	move_x += v->x * 0.05;
	move_y += v->y * 0.05;
	free (v);
	if (key == MLX_KEY_A)
		update_position(game, move_x, move_y, LEFT);
	else
		update_position(game, move_x, move_y, RIGHT);
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		ft_vector_rotate(game->plane, -0.7);
		ft_vector_rotate(game->dir, -0.7);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		ft_vector_rotate(game->plane, 0.7);
		ft_vector_rotate(game->dir, 0.7);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player_up_down(game, MLX_KEY_W);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player_up_down(game, MLX_KEY_S);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player_left_right(game, MLX_KEY_A);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_left_right(game, MLX_KEY_D);
}
