/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/16 14:01:03 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static void	free_textures(t_game *game)
{
	free(game->map->north_texture);
	free(game->map->south_texture);
	free(game->map->west_texture);
	free(game->map->east_texture);
	free(game->map->door_texture);
	free(game->map->portal_texture);
	mlx_delete_texture(game->no);
	mlx_delete_texture(game->so);
	mlx_delete_texture(game->ea);
	mlx_delete_texture(game->we);
	mlx_delete_texture(game->door);
	mlx_delete_texture(game->portal);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	free_textures(game);
	free(game->map->floor_color);
	free(game->map->ceiling_color);
	if (game->map->full_map)
	{
		while (i < MAP_HEIGHT)
			free(game->map->full_map[i++]);
		free(game->map->full_map);
	}
	free(game->map);
	free(game->player);
	free(game->pos);
	free(game->dir);
	free(game->plane);
	free(game->map_pos);
	free(game->camera_pixel);
	free(game->ray_dir);
	free(game);
}
