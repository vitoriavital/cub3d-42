/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/09/20 16:46:07 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

static void	free_textures(t_game *game)
{
	free(game->map->north_texture);
	free(game->map->south_texture);
	free(game->map->west_texture);
	free(game->map->east_texture);
	mlx_delete_texture(game->no);
	mlx_delete_texture(game->so);
	mlx_delete_texture(game->ea);
	mlx_delete_texture(game->we);
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
