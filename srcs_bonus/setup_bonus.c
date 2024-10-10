/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:48:48 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/08 16:26:55 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

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

void	print_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
			printf("%c", game->map->full_map[y][x++]);
		printf("\n");
		y++;
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
	return (0);
}

int	add_full_map(t_game *game)
{
	game->map->full_map = malloc(MAP_HEIGHT * sizeof(char *));
	if (!game->map->full_map)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		free(game->player);
		free(game->map);
		return (-1);
	}
	return (0);
}

int	full_map_error(int i, t_game *game)
{
	int	j;

	fprintf(stderr, "Memory allocation failed.\n");
	j = 0;
	while (j < i)
		free(game->map->full_map[j++]);
	free(game->map->full_map);
	free(game->player);
	free(game->map);
	return (-1);
}

int	fill_full_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	const char *fixed_map[10] = {
		"1111111111",
		"1000010001",
		"1010000001",
		"1000000001",
		"1000100001",
		"1000000001",
		"1000000001",
		"1010000001",
		"1000000001",
		"1111111111",
	};
	while (i < MAP_HEIGHT)
	{
		game->map->full_map[i] = ft_strdup(fixed_map[i]);
		if (!game->map->full_map[i])
			return (full_map_error(i, game));
		i++;
	}
	return (0);
}

int	read_map(char *map_file, t_game *game)
{
	if (add_player_map(game) == -1)
		return (-1);
	game->map->north_texture = ft_strdup("textures/seamless_stone.png");
	game->map->south_texture = ft_strdup("textures/sunflowers.png");
	game->map->west_texture = ft_strdup("textures/the_scream.png");
	game->map->east_texture = ft_strdup("textures/the_starry_night.png");
	game->no = mlx_load_png(game->map->north_texture);
	game->so = mlx_load_png(game->map->south_texture);
	game->ea = mlx_load_png(game->map->east_texture);
	game->we = mlx_load_png(game->map->west_texture);
	game->map->floor_color = ft_strdup("220,100,0");
	game->map->ceiling_color = ft_strdup("225,30,0");
	if (add_full_map(game) == -1)
		return (-1);
	if (fill_full_map(game) == -1)
		return (-1);
	game->player->line = 3;
	game->player->column = 4;
	game->player->dir = NORTH;
	game->pos = ft_vector_create(game->player->line, game->player->column);
	player_direction(game);
	game->map_pos = ft_vector_create(0, 0);
	game->camera_pixel = ft_vector_create(0, 0);
	game->ray_dir = ft_vector_create(0, 0);
	return (0);
}
