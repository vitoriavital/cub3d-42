/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_portal_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:26:38 by mavitori          #+#    #+#             */
/*   Updated: 2024/10/16 16:40:35 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static int	check_no(float *last_open, int x, int y, t_game *game)
{
	if (game->map->full_map[x][y - 1] == '2')
	{
		game->map->full_map[x][y - 1] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y - 1] == '3')
	{
		game->map->full_map[x][y - 1] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y - 1] == '4')
	{
		printf("Enter portal! \n");
		*last_open = mlx_get_time();
		return (1);
	}
	return (0);
}

static int	check_so(float *last_open, int x, int y, t_game *game)
{
	if (game->map->full_map[x][y + 1] == '2')
	{
		game->map->full_map[x][y + 1] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y + 1] == '3')
	{
		game->map->full_map[x][y + 1] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x][y + 1] == '4')
	{
		printf("Enter portal! \n");
		*last_open = mlx_get_time();
		return (1);
	}
	return (0);
}

static int	check_we(float *last_open, int x, int y, t_game *game)
{
	if (game->map->full_map[x - 1][y] == '2')
	{
		game->map->full_map[x - 1][y] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x - 1][y] == '3')
	{
		game->map->full_map[x - 1][y] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x - 1][y] == '4')
	{
		printf("Enter portal! \n");
		*last_open = mlx_get_time();
		return (1);
	}
	return (0);
}

static int	check_ea(float *last_open, int x, int y, t_game *game)
{
	if (game->map->full_map[x + 1][y] == '2')
	{
		game->map->full_map[x + 1][y] = '3'; // open door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x + 1][y] == '3')
	{
		game->map->full_map[x + 1][y] = '2'; // close door
		*last_open = mlx_get_time();
		return (1);
	}
	else if (game->map->full_map[x + 1][y] == '4')
	{
		printf("Enter portal! \n");
		*last_open = mlx_get_time();
		return (1);
	}
	return (0);
}

void	switch_door_portal(t_game *game)
{
	int				x;
	int				y;
	static float	last_open;

	x = (int)game->map_pos->x;
	y = (int)game->map_pos->y;
	// printf("Current: %f | Last open: %f \n", mlx_get_time(), last_open);
	if (mlx_get_time() - last_open < 0.5)
	{
		printf("Too fast! \n");
		return ;
	}
	// printf("Time: %f\n", mlx_get_time());
	// printf("Position: x %d | y %d = %d \n", x, y, game->map->full_map[x][y - 1]);
	printf("Ray dir: x=%f | y=%f \n", game->dir->x, game->dir->y);
	// if (game->dir->y < 0 && game->dir->x == 0 && check_no(&last_open, x, y, game) != 0 )
	// 	return ;
	// else if (game->dir->x == 0 && check_so(&last_open, x, y, game) != 0)
	// 	return ;
	// if (game->dir->x < 0 && game->dir->y == 0 && check_we(&last_open, x, y, game) != 0)
	// 	return ;
	// else if (game->dir->y == 0 && check_ea(&last_open, x, y, game) != 0)
	// 	return ;
	int	dir_x = game->dir->x;
	int	dir_y = game->dir->y;

	if (game->map->full_map[x + dir_x][y + dir_y] == '2')
	{
		game->map->full_map[x + dir_x][y + dir_y] = '3'; // open door
		last_open = mlx_get_time();
		return ;
	}
	else if (game->map->full_map[x + dir_x][y + dir_y] == '3')
	{
		game->map->full_map[x + dir_x][y + dir_y] = '2'; // close door
		last_open = mlx_get_time();
		return ;
	}
	else if (game->map->full_map[x + dir_x][y + dir_y] == '4')
	{
		printf("Enter portal! \n");
		last_open = mlx_get_time();
		return ;
	}

	last_open = mlx_get_time();
}
