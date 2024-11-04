/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:48 by mavitori          #+#    #+#             */
/*   Updated: 2024/11/04 14:15:39 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

static void	player_direction(t_game *game)
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

static int	add_player_map(t_game *game)
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
	game->map->full_map = NULL;
	game->map->north_texture = NULL;
	game->map->south_texture = NULL;
	game->map->east_texture = NULL;
	game->map->west_texture = NULL;
	return (0);
}

static int	load_textures(t_game *game)
{
	mlx_texture_t	*texture;

	game->so = NULL;
	game->no = NULL;
	game->ea = NULL;
	game->we = NULL;
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
	if (verify_extension(map_file) == -1)
		return (-1);
	if (add_player_map(game) == -1 || read_file(map_file, game) == -1)
		return (-1);
	if (load_textures(game) == -1)
		return (error_parser("Texture failed to load", NULL));
	game->pos = ft_vector_create(game->player->line, game->player->column);
	player_direction(game);
	game->map_pos = ft_vector_create(0, 0);
	game->camera_pixel = ft_vector_create(0, 0);
	game->ray_dir = ft_vector_create(0, 0);
	return (0);
}
