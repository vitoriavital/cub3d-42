/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_portal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:26:38 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/17 10:40:41 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	check_door_portal(float *last_open, int x, int y, t_game *game)
{
	if (game->map->full_map[x][y] == '2')
	{
		game->map->full_map[x][y] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y] == '3')
	{
		game->map->full_map[x][y] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y] == '4')
	{
		printf("Enter portal! \n");
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
	return -1;
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
	if (dir == NORTH && check_door_portal(&last_open, x, y - 1, game) != 0)
		return ;
	else if (dir == SOUTH && check_door_portal(&last_open, x, y + 1, game) != 0)
		return ;
	if (dir == WEST && check_door_portal(&last_open, x - 1, y, game) != 0)
		return ;
	else if (dir == EAST && check_door_portal(&last_open, x + 1, y, game) != 0)
		return ;

	last_open = mlx_get_time();
}
