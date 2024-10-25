/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:48 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/25 13:03:34 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	verify_extension(char *map_file)
{
	int	len;

	len = 0;
	while (map_file[len])
		len++;
	if (ft_strncmp(&map_file[len - 4], ".cub", 4) == 0)
		return (0);
	printf("Error: The file need be .cub\n");
	return (-1);
}

void	player_direction(t_game *game)
{
	if (game->player->dir == NORTH)
	{
		game->dir = ft_vector_create(0, -1);
		game->plane = ft_vector_create(0.66, 0);
	}
	else if (game->player->dir == SOUTH)
	{
		game->dir = ft_vector_create(0, 1);
		game->plane = ft_vector_create(-0.66, 0);
	}
	else if (game->player->dir == EAST)
	{
		game->dir = ft_vector_create(1, 0);
		game->plane = ft_vector_create(0, 0.66);
	}
	else if (game->player->dir == WEST)
	{
		game->dir = ft_vector_create(-1, 0);
		game->plane = ft_vector_create(0, -0.66);
	}
}

int	add_player_map(t_game *game)
{
	t_player	*player;
	t_map		*map;

	player = malloc(sizeof(t_player));
	map = malloc(sizeof(t_map));
	if (!player || !map)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		return (-1);
	}
	game->player = player;
	game->map = map;
	game->map->ceiling_color = NULL;
	game->map->floor_color = NULL;
	game->map->old_ceiling_color = NULL;
	game->map->old_floor_color = NULL;
	game->map->full_map = NULL;
	game->map->north_texture = NULL;
	game->map->south_texture = NULL;
	game->map->east_texture = NULL;
	game->map->west_texture = NULL;
	return (0);
}

int	load_textures(t_game *game)
{
	mlx_texture_t	*texture;

	game->so = NULL;
	game->no = NULL;
	game->ea = NULL;
	game->we = NULL;
	game->portal = NULL;
	game->door = NULL;
	texture = mlx_load_png(game->map->north_texture);
	if (!texture)
		return (-1);
	game->no = texture;
	texture = mlx_load_png(game->map->south_texture);
	if (!texture)
		return (-1);
	game->so = texture;
	texture = mlx_load_png(game->map->east_texture);
	if (!texture)
		return (-1);
	game->ea = texture;
	texture = mlx_load_png(game->map->west_texture);
	if (!texture)
		return (-1);
	game->we = texture;
	texture = mlx_load_png(game->map->door_texture);
	if (!texture)
		return (-1);
	game->door = texture;
	texture = mlx_load_png(game->map->portal_texture);
	if (!texture)
		return (-1);
	game->portal = texture;
	char *ceiling = ft_strdup("textures/ceiling.png");
	texture = mlx_load_png(ceiling);
	if (!texture)
		return (-1);
	game->ceiling = texture;
	free (ceiling);
	char *floor = ft_strdup("textures/floor.png");
	texture = mlx_load_png(floor);
	if (!texture)
		return (-1);
	game->floor = texture;
	free (floor);
	return (0);
}

int	read_map(char *map_file, t_game *game)
{
	game->map = NULL;
	game->player = NULL;
	game->map_fill = NULL;
	game->pos = NULL;
	game->dir = NULL;
	game->plane = NULL;
	game->map_pos = NULL;
	game->camera_pixel = NULL;
	game->ray_dir = NULL;
	game->so = NULL;
	game->no = NULL;
	game->ea = NULL;
	game->we = NULL;
	game->bonus_textures = 0;
	if (verify_extension(map_file) == -1)
		return (-1);
	if (add_player_map(game) == -1 || read_file(map_file, game) == -1)
		return (-1);
	if (load_textures(game) == -1)
		return (-1);
	game->pos = ft_vector_create(game->player->line, game->player->column);
	player_direction(game);
	game->map_pos = ft_vector_create(0, 0);
	game->camera_pixel = ft_vector_create(0, 0);
	game->ray_dir = ft_vector_create(0, 0);
	return (0);
}
