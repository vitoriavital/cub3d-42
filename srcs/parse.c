/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/11/04 14:56:10 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

static int	split_content(char **content, char **config,
	char **map, char **map_fill)
{
	int	i;
	int	j;
	int	h;

	i = 0;
	j = 0;
	h = 0;
	while (content[i])
	{
		if (check_config_signal(content[i]) == 0)
		{
			if (map[0] != NULL)
				return (-1);
			config[j++] = ft_strdup(content[i]);
		}
		else
		{
			map_fill[h] = ft_strdup(content[i]);
			map[h++] = ft_strdup(content[i]);
		}
		i++;
	}
	free_split(content);
	return (0);
}

static int	handle_config_validation(char **content)
{
	int	i;

	i = 0;
	if (!content[0])
		return (error_parser("Empty File", content));
	while (check_config_signal(content[i]) == 0)
		i++;
	if (i != 6)
		return (error_parser("Invalid config", content));
	return (i);
}

int	parser_file(char *full_content, t_game *game)
{
	char	**config;
	char	**map;
	char	**map_fill;
	char	**content;
	int		i;

	if (check_spaces(full_content) == -1)
		return (error_parser("Check the map", NULL));
	content = ft_split(full_content, '\n');
	i = handle_config_validation(content);
	if (i == -1)
		return (-1);
	config = (char **)ft_calloc(sizeof(char *), 7);
	while (content[i])
		i++;
	map = (char **)ft_calloc(sizeof(char *), (i - 5));
	map_fill = (char **)ft_calloc(sizeof(char *), (i - 5));
	if (split_content(content, config, map, map_fill) == -1)
		return (error_parser("Invalid order", NULL));
	game->map_fill = map_fill;
	if (check_config(config, game, map) == -1 || check_map(map, game) == -1)
		return (error_parser("Invalid config", config));
	game->map->full_map = map;
	free_split(config);
	return (0);
}
