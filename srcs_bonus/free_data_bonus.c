/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:18:18 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	check_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

static void	free_textures(t_game *game)
{
	check_free(game->map->north_texture);
	check_free(game->map->south_texture);
	check_free(game->map->east_texture);
	check_free(game->map->west_texture);
	check_free(game->map->door_texture);
	check_free(game->map->portal_texture);
	if (game->no)
		mlx_delete_texture(game->no);
	if (game->so)
		mlx_delete_texture(game->so);
	if (game->ea)
		mlx_delete_texture(game->ea);
	if (game->we)
		mlx_delete_texture(game->we);
	if (game->door)
		mlx_delete_texture(game->door);
	if (game->portal)
		mlx_delete_texture(game->portal);
}

int	free_invalid_content(char **config, char **map)
{
	printf("Error: Invalid content.\n");
	free_split(config);
	free_split(map);
	return (-1);
}

void	free_game(t_game *game)
{
	if (!game->map)
		return (check_free(game));
	free_textures(game);
	if (game->map)
	{
		check_free(game->map->floor_color);
		check_free(game->map->ceiling_color);
		check_free(game->map->old_floor_color);
		check_free(game->map->old_ceiling_color);
	}
	if (game->map->full_map)
		free_split(game->map->full_map);
	check_free(game->map);
	check_free(game->player);
	check_free(game->pos);
	check_free(game->dir);
	check_free(game->plane);
	check_free(game->map_pos);
	check_free(game->camera_pixel);
	check_free(game->ray_dir);
	if (game->map_fill)
		free_split(game->map_fill);
	check_free(game);
}

void	free_split(char **content)
{
	int	i;

	i = 0;
	if (!content)
		return ;
	while (content[i])
	{
		if (content[i])
			free(content[i++]);
		else
			i++;
	}
	if (content)
		free(content);
}