/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/25 15:29:59 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

int	check_sides(char **map, int x, int y)
{
	if (map[x - 1][y] == '0' || map[x - 1][y] == '\0' || map[x - 1][y] == ' ')
		return (-1);
	if (map[x + 1] == NULL || (map[x + 1][y] == '0'
		|| map[x + 1][y] == '\0' || map[x + 1][y] == ' '))
		return (-1);
	if (map[x][y - 1] == '0' || map[x][y - 1] == '\0' || map[x][y - 1] == ' ')
		return (-1);
	if (map[x][y + 1] == '\0' || (map[x][y + 1] == '0' || map[x][y + 1] == ' '))
		return (-1);
	return (0);
}

int	check_bishop(char **map, int x, int y)
{
	if (map[x - 1][y - 1] == '0' || map[x - 1][y - 1] == '\0'
		|| map[x - 1][y - 1] == ' ')
		return (-1);
	if (map[x - 1][y + 1] == '\0' || map[x - 1][y + 1] == '0'
		|| map[x - 1][y + 1] == ' ')
		return (-1);
	if (map[x + 1] == NULL || (map[x + 1][y - 1] == '0'
		|| map[x + 1][y - 1] == '\0' || map[x + 1][y - 1] == ' '))
		return (-1);
	if (map[x + 1] == NULL || map[x + 1][y + 1] == '\0'
		|| map[x + 1][y + 1] == '0' || map[x + 1][y + 1] == ' ')
		return (-1);
	return (0);
}

int	double_check(char **map_fill, int x, int y)
{
	if (check_sides(map_fill, x, y) == -1)
		return (-1);
	if (check_bishop(map_fill, x, y) == -1)
		return (-1);
	return (0);
}

int	is_f_exposed(t_game *game)
{
	int	x;
	int	y;
	int	f;

	x = 0;
	y = 0;
	f = 0;
	while (game->map_fill[x] != NULL)
	{
		y = 0;
		while (game->map_fill[x][y] != '\0')
		{
			if (game->map_fill[x][y] == 'F')
			{
				if (double_check(game->map_fill, x, y) == -1)
					return (-1);
				f++;
			}
			y++;
		}
		x++;
	}
	if (f == 0)
		return (-1);
	return (0);
}

int	check_map(char **lines, t_game *game)
{
	int	i;
	int	line;
	int	player;

	line = 0;
	i = 0;
	player = 0;
	while (lines[line])
	{
		while (lines[line][i])
		{
			if (ft_strrchr(" 0124NSWE", lines[line][i]) == NULL)
				return (error_parser("Error: Wrong caracter", lines));
			count_player(lines[line][i], &player);
			i++;
		}
		line++;
		i = 0;
	}
	if (player != 1)
		return (-1);
	set_position(lines, game);
	if (is_f_exposed(game) == -1)
		return (error_parser("Error: Wrong caracter", lines));
	return (0);
}