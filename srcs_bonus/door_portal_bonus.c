/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_portal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:06 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 13:18:45 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	upside_down(t_game *game)
{
	char	*new_floor;
	char	*new_ceiling;

	game->no = mlx_load_png(game->map->north_texture);
	game->so = mlx_load_png(game->map->south_texture);
	game->ea = mlx_load_png(game->map->east_texture);
	game->we = mlx_load_png(game->map->west_texture);
	game->door = mlx_load_png(game->map->door_texture);
	game->portal = mlx_load_png(game->map->portal_texture);
	game->particle_color = 0x00000000;
	new_floor = ft_strdup("0,0,0");
	new_ceiling = ft_strdup("140,0,0");
	game->map->old_floor_color = game->map->floor_color;
	game->map->old_ceiling_color = game->map->ceiling_color;
	game->map->floor_color = new_floor;
	game->map->ceiling_color = new_ceiling;
	apply_dark_filter(game->no);
	apply_dark_filter(game->so);
	apply_dark_filter(game->we);
	apply_dark_filter(game->ea);
	apply_dark_filter(game->door);
	apply_dark_filter(game->portal);
	apply_dark_filter(game->floor);
	apply_dark_filter(game->ceiling);
}

static void	enter_portal(t_game *game)
{
	static int	normal;

	mlx_delete_texture(game->no);
	mlx_delete_texture(game->so);
	mlx_delete_texture(game->ea);
	mlx_delete_texture(game->we);
	mlx_delete_texture(game->door);
	mlx_delete_texture(game->portal);
	if (normal == 0)
	{
		upside_down(game);
		normal = 1;
	}
	else
	{
		mlx_delete_texture(game->floor);
		mlx_delete_texture(game->ceiling);
		reload_normal_setup(game);
		normal = 0;
	}
}

static int	player_enter_portal(t_game *game, int dir)
{
	if (dir == NORTH)
		move_player_up_down(game, MLX_KEY_W, -2);
	else if (dir == SOUTH)
		move_player_up_down(game, MLX_KEY_S, 2);
	else if (dir == EAST)
		move_player_left_right(game, MLX_KEY_A, 2);
	else
		move_player_left_right(game, MLX_KEY_D, -2);
	return (1);
}

static int	check_door_portal(int col, int row, t_game *game, int dir)
{
	if (game->map->full_map[row][col] == '2')
	{
		game->map->full_map[row][col] = '3';
		return (1);
	}
	else if (game->map->full_map[row][col] == '3')
	{
		game->map->full_map[row][col] = '2';
		return (1);
	}
	else if (game->map->full_map[row][col] == '4')
	{
		enter_portal(game);
		return (player_enter_portal(game, dir));
	}
	return (0);
}

void	switch_door_portal(t_game *game)
{
	int				x;
	int				y;
	static float	last_open;
	int				dir;

	x = (int)game->map_pos->x;
	y = (int)game->map_pos->y;
	if (mlx_get_time() - last_open < 0.4)
		return ;
	dir = find_direction(game);
	if (dir == NORTH
		&& check_door_portal(x, y - 1, game, dir) != 0)
		return ;
	else if (dir == SOUTH
		&& check_door_portal(x, y + 1, game, dir) != 0)
		return ;
	if (dir == WEST && check_door_portal(x - 1, y, game, dir) != 0)
		return ;
	else if (dir == EAST
		&& check_door_portal(x + 1, y, game, dir) != 0)
		return ;
	last_open = mlx_get_time();
}
