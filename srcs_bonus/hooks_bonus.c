/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:51:27 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/17 10:15:52 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	check_wall(t_game *game, float x, float y, int dir)
{
	int	row;
	int	column;

	row = (int)y;
	column = (int)x;
	if (row < 0 || row >= MAP_HEIGHT || column < 0 || column >= MAP_WIDTH)
		return (-1);
	if (game->map->full_map[row][column] == '0' || game->map->full_map[row][column] == '3')
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

void	move_player_up_down(t_game *game, int key, int multiplier)
{
	float	move_x;
	float	move_y;

	move_x = 0.0;
	move_y = 0.0;
	if (key == MLX_KEY_W)
	{
		if (multiplier == 10)
			update_position(game, 0, -2, UP);
		else
		{
			move_x += game->dir->x * 0.05 * multiplier;
			move_y += game->dir->y * 0.05 * multiplier;
			update_position(game, move_x, move_y, UP);
		}
	}
	if (key == MLX_KEY_S)
	{
		move_x -= game->dir->x * 0.05 * multiplier;
		move_y -= game->dir->y * 0.05 * multiplier;
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
static void	mouse_rotation(t_game *game)
{
	int		x;
	int		y;
	float	angle;
	float	side;

	x = 0;
	y = 0;
	angle = 0.4;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	side = x - (SCREEN_WIDTH / 2);
	if (side < 0)
		angle *= -1;
	else
		angle *= 1;
	ft_vector_rotate(game->plane, angle);
	ft_vector_rotate(game->dir, angle);
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if ((mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT)))
		mouse_rotation(game);
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
		move_player_up_down(game, MLX_KEY_W, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player_up_down(game, MLX_KEY_S, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player_left_right(game, MLX_KEY_A);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_left_right(game, MLX_KEY_D);
	if (mlx_is_key_down(game->mlx, MLX_KEY_O))
		switch_door_portal(game);
}
