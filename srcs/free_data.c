/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:50:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/11/04 14:14:19 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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
	if (game->no)
		mlx_delete_texture(game->no);
	if (game->so)
		mlx_delete_texture(game->so);
	if (game->ea)
		mlx_delete_texture(game->ea);
	if (game->we)
		mlx_delete_texture(game->we);
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
