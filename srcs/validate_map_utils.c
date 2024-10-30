/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/30 20:28:38 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	count_player(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	return ;
}

int	see_where(char c, t_game *game)
{
	if (c == 'N')
		return (game->player->dir = NORTH);
	else if (c == 'S')
		return (game->player->dir = SOUTH);
	else if (c == 'E')
		return (game->player->dir = EAST);
	else if (c == 'W')
		return (game->player->dir = WEST);
	return (10);
}

int	set_position(char **map, t_game *game, int players)
{
	int	i;
	int	j;

	i = 0;
	if (players != 1)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (see_where(map[i][j], game) != 10)
			{
				game->player->column = i;
				game->player->line = j;
				map[i][j] = '0';
				game->map_fill[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	flood_fill(game, game->player->column, game->player->line);
	return (0);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || !game->map_fill[x]
		|| y >= (int)ft_strlen(game->map_fill[x])
		|| game->map_fill[x][y] != '0')
		return ;
	game->map_fill[x][y] = 'F';
	if (game->map_fill[x + 1])
		flood_fill(game, x + 1, y);
	if (x - 1 >= 0 && game->map_fill[x - 1])
		flood_fill(game, x - 1, y);
	if (y + 1 < (int)ft_strlen(game->map_fill[x]))
		flood_fill(game, x, y + 1);
	if (y - 1 >= 0)
		flood_fill(game, x, y - 1);
}
