/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/21 21:01:17 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int	check_sides(char **map, int x, int y)
{
	//cimaa
	if (map[x-1][y] == '0' || map[x-1][y] == '\0' || map[x-1][y] == ' ')
		return (-1);
	// baixo
	if (map[x+1] == NULL || (map[x+1][y] == '0' || map[x+1][y] == '\0' || map[x+1][y] == ' '))
		return (-1);
	// esquerda
	if (map[x][y-1] == '0' || map[x][y-1] == '\0' || map[x][y-1] == ' ')
		return (-1);
	// direita
	if (map[x][y+1] == '\0' || (map[x][y+1] == '0' || map[x][y+1] == ' '))
		return (-1);
	return (0);
}

int	check_bishop(char **map, int x, int y)
{
	// superior esquerda
	if (map[x-1][y-1] == '0' || map[x-1][y-1] == '\0' || map[x-1][y-1] == ' ')
		return (-1);
	// superior direita
	if (map[x-1][y+1] == '\0' || map[x-1][y+1] == '0' || map[x-1][y+1] == ' ')
		return (-1);
	// inferior esquerda
	if (map[x+1] == NULL || (map[x+1][y-1] == '0' || map[x+1][y-1] == '\0' || map[x+1][y-1] == ' '))
		return (-1);
	// inferior direita
	if (map[x+1] == NULL || map[x+1][y+1] == '\0' || map[x+1][y+1] == '0'  || map[x+1][y+1] == ' ')
		return (-1);
	return (0);
}

int	is_f_exposed(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (game->map_fill[x] != NULL)
	{
		y = 0;
		while (game->map_fill[x][y] != '\0')
		{
			if (game->map_fill[x][y] == 'F')
			{
				if (check_sides(game->map_fill, x, y) == -1)
				{
					// printf("Invalid map: The map missing wall.\n");
					return (-1);
				}
				if (check_bishop(game->map_fill, x, y) == -1)
				{
					// printf("Invalid map: The map missing wall.\n");
					return (-1);
				}
			}
			y++;
		}
		x++;
	}
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
			if (ft_strrchr(" 01NSWE", lines[line][i]) == NULL)
				return (-1);
			count_player(lines[line][i], &player);
			i++;
		}
		line++;
		i = 0;
	}
	if (player != 1)
		return (-1);
	set_position(lines, game);
	return (is_f_exposed(game));
}
