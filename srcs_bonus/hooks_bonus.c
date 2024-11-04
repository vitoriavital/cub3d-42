/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:51:27 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 12:06:09 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	activate_textures_bonus(t_game *game)
{
	static float	last_open;

	if (mlx_get_time() - last_open < 0.4)
		return ;
	game->bonus_textures = !game->bonus_textures;
	last_open = mlx_get_time();
}

static void	movements_hooks(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player_up_down(game, MLX_KEY_W, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player_up_down(game, MLX_KEY_S, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player_left_right(game, MLX_KEY_A, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player_left_right(game, MLX_KEY_D, 1);
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
	movements_hooks(game);
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_O))
		switch_door_portal(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
		activate_textures_bonus(game);
}
