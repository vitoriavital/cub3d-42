/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/11/03 12:59:00 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int	split_content(char **content, char **config, char **map, char **map_fill)
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
	{
		free_split(content);
		return (-1);
	}
	while (check_config_signal(content[i]) == 0)
		i++;
	if (i != 6)
	{
		printf("Error: Invalid config.\n");
		free_split(content);
		return (-1);
	}
	return (i);
}

int	error_parser(char *text, char **config)
{
	if (config != NULL)
		free_split(config);
	printf("Error: %s\n", text);
	return (-1);
}


int check_all_spaces(char *content, int j)
{
	while (content[j])
	{
		if (!ft_isspace(content[j]))
			return (-1);
		j++;
	}
	return (0);
}

int	check_new_line(char c)
{
	if (c == '\n')
		return (1);
	else
		return (0);
}

int check_spaces(char *content)
{
	int	i;
	int	map_started;
	int	last_was_newline;
	int	j;

	map_started = 0;
	last_was_newline = 1;
	i  = 0;
	while (content[i])
	{
		if (content[i] == '1' && last_was_newline)
			map_started = 1;
		if (map_started && content[i] == '\n')
		{
			j = i + 1;
			while (content[j] && ft_isspace(content[j]) && content[j] != '\n')
				j++;
			if (content[j] == '\n')
				return (check_all_spaces(content, j));
		}
		last_was_newline = check_new_line(content[i]);
		i++;
	}
	return (0);
}

int	parser_file(char *full_content, t_game *game)
{
	char	**config;
	char	**map;
	char	**map_fill;
	char	**content;
	int		i;

	if (check_spaces(full_content) == -1)
		return (error_parser("Error: Check the map", NULL));
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
		return (error_parser("Error: Invalid order.", NULL));
	game->map_fill = map_fill;
	if (check_config(config, game, map) == -1 || check_map(map, game) == -1)
		return (error_parser(".", config));
	game->map->full_map = map;
	free_split(config);
	return (0);
}
