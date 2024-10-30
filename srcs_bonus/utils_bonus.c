/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:09:21 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/30 12:56:33 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

void	define_wall_type(t_game *game, t_dda *dda, int x, int y)
{
	if (game->map->full_map[y][x] == '2')
		dda->wall_type = DOOR;
	else if (game->map->full_map[y][x] == '4')
		dda->wall_type = PORTAL;
	else if (game->map->full_map[y][x] == '1')
		dda->wall_type = WALL;
}

int	check_tex(t_game *game, char *key, char *tex_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(tex_path);
	if (!texture)
		return (-1);
	if (ft_strncmp(key, "no", 2) == 0)
		game->no = texture;
	else if (ft_strncmp(key, "so", 2) == 0)
		game->so = texture;
	else if (ft_strncmp(key, "ea", 2) == 0)
		game->ea = texture;
	else if (ft_strncmp(key, "we", 2) == 0)
		game->we = texture;
	else if (ft_strncmp(key, "so", 2) == 0)
		game->so = texture;
	else if (ft_strncmp(key, "door", 4) == 0)
		game->door = texture;
	else if (ft_strncmp(key, "portal", 6) == 0)
		game->portal = texture;
	else if (ft_strncmp(key, "floor", 5) == 0)
		game->floor = texture;
	else if (ft_strncmp(key, "ceiling", 7) == 0)
		game->ceiling = texture;
	return (0);
}

int	find_direction(t_game *game)
{
	if (game->dir->y < 0 && game->dir->x < 0.2 && game->dir->x > -0.2)
		return (NORTH);
	else if (game->dir->y > 0 && game->dir->x < 0.2 && game->dir->x > -0.2)
		return (SOUTH);
	if (game->dir->x < 0 && game->dir->y < 0.2 && game->dir->y > -0.2)
		return (WEST);
	else if (game->dir->x > 0 && game->dir->y < 0.2 && game->dir->y > -0.2)
		return (EAST);
	return (-2);
}

void	reload_normal_setup(t_game *game)
{
	char	*tmp_floor;
	char	*tmp_ceiling;

	game->no = mlx_load_png(game->map->north_texture);
	game->so = mlx_load_png(game->map->south_texture);
	game->ea = mlx_load_png(game->map->east_texture);
	game->we = mlx_load_png(game->map->west_texture);
	game->door = mlx_load_png(game->map->door_texture);
	game->portal = mlx_load_png(game->map->portal_texture);
	game->ceiling = mlx_load_png(game->map->ceiling_texture);
	game->floor = mlx_load_png(game->map->floor_texture);
	tmp_floor = game->map->floor_color;
	tmp_ceiling = game->map->ceiling_color;
	game->map->floor_color = game->map->old_floor_color;
	game->map->ceiling_color = game->map->old_ceiling_color;
	game->map->old_floor_color = tmp_floor;
	game->map->old_ceiling_color = tmp_ceiling;
	game->particle_color = 0xFFFFFFFF;
}
