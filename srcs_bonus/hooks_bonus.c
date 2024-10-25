/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:51:27 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/25 15:15:28 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	check_wall(t_game *game, float x, float y)
{
	int	row;
	int	column;

	row = (int)y;
	column = (int)x;
	if (game->map->full_map[row][column] == '0' || game->map->full_map[row][column] == '3')
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
	if (multiplier == 10)
	{
		if (key == MLX_KEY_W)
			update_position(game, 0, -2);
		else
			update_position(game, 0, 2);
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
	if (multiplier == 10)
	{
		if (key == MLX_KEY_A)
			update_position(game, 2, 0);
		else
			update_position(game, -2, 0);
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

static void	activate_textures_bonus(t_game *game)
{
	static float	last_open;

	if (mlx_get_time() - last_open < 0.4)
		return ;
	game->bonus_textures = !game->bonus_textures;
	last_open = mlx_get_time();
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
		move_player_left_right(game, MLX_KEY_A, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_left_right(game, MLX_KEY_D, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_O))
		switch_door_portal(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		activate_textures_bonus(game);
}
