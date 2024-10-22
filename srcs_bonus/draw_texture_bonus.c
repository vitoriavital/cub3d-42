/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:42:01 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/22 17:35:32 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static uint32_t	fix_color(mlx_texture_t *texture, t_wall *wall)
{
	uint8_t	*color;

	color = &texture->pixels[(wall->tex_y * texture->width + wall->tex_x) \
		* texture->bytes_per_pixel];
	return (ft_pixel(color[0], color[1], color[2], color[3]));
}

static void	calculate_texture_x(t_dda *dda, t_game *game, t_wall *wall)
{
	if (dda->hit_side == 0)
		wall->x = (game->pos->y + dda->player_dist_wall * game->ray_dir->y);
	else
		wall->x = (game->pos->x + dda->player_dist_wall * game->ray_dir->x);
	wall->x -= floor(wall->x);
	wall->tex_x = (int)(wall->x * wall->tex_width);
	if (dda->hit_side == 0 && game->ray_dir->x < 0)
		wall->tex_x = wall->tex_width - wall->tex_x - 1;
	if (dda->hit_side == 1 && game->ray_dir->y > 0)
		wall->tex_x = wall->tex_width - wall->tex_x - 1;
	wall->step = 1.0 * wall->tex_height / wall->height;
	wall->tex_pos = (wall->start - SCREEN_HEIGHT / 2 + wall->height / 2) \
	* wall->step;
}

static void	wall_direction(t_game *game, t_dda *dda)
{
	if (dda->hit_side == 0 && dda->wall_type == WALL)
	{
		if (game->ray_dir->x < 0)
			game->texture = game->we;
		else
			game->texture = game->ea;
	}
	else if (dda->wall_type == WALL)
	{
		if (game->ray_dir->y < 0)
			game->texture = game->no;
		else
			game->texture = game->so;
	}
	else if (dda->wall_type == DOOR)
		game->texture = game->door;
	else
		game->texture = game->portal;
}

void	draw_wall_line(t_wall *wall, t_dda *dda, t_game *game)
{
	int				i;
	mlx_texture_t	*texture;

	wall_direction(game, dda);
	texture = game->texture;
	wall->tex_height = texture->height;
	wall->tex_width = texture->width;
	calculate_texture_x(dda, game, wall);
	i = wall->start;
	while (i < wall->end)
	{
		wall->tex_y = (int)wall->tex_pos;
		if (wall->tex_y < 0)
			wall->tex_y = 0;
		if (wall->tex_y >= wall->tex_height)
			wall->tex_y = wall->tex_height - 1;
		wall->tex_pos += wall->step;
		mlx_put_pixel(game->image, game->current_pixel, i, \
			fix_color(texture, wall));
		i++;
	}
}
