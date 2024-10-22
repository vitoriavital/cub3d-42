/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_portal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:06 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:35:01 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include_bonus/cub_3d_bonus.h"

static void	upside_down(t_game *game)
{
	char	*new_no;
	char	*new_so;
	char	*new_we;
	char	*new_ea;
	char	*new_door;
	char	*new_portal;
	char	*new_floor;
	char	*new_ceiling;

	new_no = ft_strdup("textures/upside_waterfall.png");
	new_so = ft_strdup("textures/upside_house.png");
	new_we = ft_strdup("textures/upside_field.png");
	new_ea = ft_strdup("textures/upside_forest.png");
	new_door = ft_strdup("textures/upside_door.png");
	new_portal = ft_strdup("textures/upside_tree_portal.png");
	new_floor = ft_strdup("0,0,0");
	new_ceiling = ft_strdup("140,0,0");
	mlx_delete_texture(game->no);
	mlx_delete_texture(game->so);
	mlx_delete_texture(game->ea);
	mlx_delete_texture(game->we);
	mlx_delete_texture(game->door);
	mlx_delete_texture(game->portal);
	game->no = mlx_load_png(new_no);
	game->so = mlx_load_png(new_so);
	game->ea = mlx_load_png(new_ea);
	game->we = mlx_load_png(new_we);
	game->door = mlx_load_png(new_door);
	game->portal = mlx_load_png(new_portal);
	game->map->old_floor_color = game->map->floor_color;
	game->map->old_ceiling_color = game->map->ceiling_color;
	game->map->floor_color = new_floor;
	game->map->ceiling_color = new_ceiling;
	free(new_no);
	free(new_so);
	free(new_ea);
	free(new_we);
	free(new_door);
	free(new_portal);
}

static void	enter_portal(t_game *game)
{
	static int	normal;
	char		*tmp_floor;
	char		*tmp_ceiling;

	if (normal == 0)
	{
		upside_down(game);
		normal = 1;
	}
	else
	{
		mlx_delete_texture(game->no);
		mlx_delete_texture(game->so);
		mlx_delete_texture(game->ea);
		mlx_delete_texture(game->we);
		mlx_delete_texture(game->door);
		mlx_delete_texture(game->portal);
		game->no = mlx_load_png(game->map->north_texture);
		game->so = mlx_load_png(game->map->south_texture);
		game->ea = mlx_load_png(game->map->east_texture);
		game->we = mlx_load_png(game->map->west_texture);
		game->door = mlx_load_png(game->map->door_texture);
		game->portal = mlx_load_png(game->map->portal_texture);
		tmp_floor = game->map->floor_color;
		tmp_ceiling = game->map->ceiling_color;
		game->map->floor_color = game->map->old_floor_color;
		game->map->ceiling_color = game->map->old_ceiling_color;
		game->map->old_floor_color = tmp_floor;
		game->map->old_ceiling_color = tmp_ceiling;
		normal = 0;
	}

}

static int	check_door_portal(float *last_open, int col, int row, t_game *game, int dir)
{
	static int	portal;

	if (game->map->full_map[row][col] == '2')
	{
		game->map->full_map[row][col] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[row][col] == '3')
	{
		game->map->full_map[row][col] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[row][col] == '4')
	{
		enter_portal(game);
		portal++;
		if (dir == NORTH)
			move_player_up_down(game, MLX_KEY_W, 10);
		else if (dir == SOUTH)
			move_player_up_down(game, MLX_KEY_S, 10);
		else if (dir == EAST)
			move_player_left_right(game, MLX_KEY_A, 10);
		else
			move_player_left_right(game, MLX_KEY_D, 10);
		*last_open = mlx_get_time();
		return (1);
	}
	return (0);
}

static int	find_direction(t_game *game)
{
	if (game->dir->y < 0 && game->dir->x < 0.2 && game->dir->x > -0.2)
		return NORTH;
	else if (game->dir->y > 0 && game->dir->x < 0.2 && game->dir->x > -0.2)
		return SOUTH;
	if (game->dir->x < 0 && game->dir->y < 0.2 && game->dir->y > -0.2)
		return WEST;
	else if (game->dir->x > 0 && game->dir->y < 0.2 && game->dir->y > -0.2)
		return EAST;
	return -2;
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
	if (dir == NORTH && check_door_portal(&last_open, x, y - 1, game, dir) != 0)
		return ;
	else if (dir == SOUTH && check_door_portal(&last_open, x, y + 1, game, dir) != 0)
		return ;
	if (dir == WEST && check_door_portal(&last_open, x - 1, y, game, dir) != 0)
		return ;
	else if (dir == EAST && check_door_portal(&last_open, x + 1, y, game, dir) != 0)
		return ;

	last_open = mlx_get_time();
}
