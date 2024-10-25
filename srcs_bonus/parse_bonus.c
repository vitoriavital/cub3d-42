/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/25 13:25:21 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/cub_3d_bonus.h"

static char	*read_file_content(char *map_file)
{
	int		fd;
	char	*line;
	char	*full_content;
	char	*temp;

	fd = open(map_file, O_RDONLY);
	if (fd < 1)
	{
		printf("Error: File error or not exist.\n");
		return (NULL);
	}
	full_content = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		temp = full_content;
		full_content = ft_strjoin(full_content, line);
		free(line);
		free(temp);
	}
	close(fd);
	return (full_content);
}

static int	split_content(char **content, char **config,
	char **map, char **map_fill)
{
	int		i;
	int		j;
	int		h;

	i = 0;
	j = 0;
	h = 0;
	while (content[i])
	{
		if (check_config_signal(content[i]) == 0)
			config[j++] = ft_strdup(content[i]);
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

static int	parser_file(char *full_content, t_game *game)
{
	char	**config;
	char	**map;
	char	**map_fill;
	char	**content;
	int		i;

	content = ft_split(full_content, '\n');
	i = handle_config_validation(content);
	if (i == -1)
		return (-1);
	config = (char **)ft_calloc(sizeof(char *), 7);
	while (content[i])
		i++;
	game->map->height = i - 6;
	map = (char **)ft_calloc(sizeof(char *), (i - 5));
	map_fill = (char **)ft_calloc(sizeof(char *), (i - 5));
	split_content(content, config, map, map_fill);
	game->map_fill = map_fill;
	if (check_config(config, game) == -1 || check_map(map, game) == -1)
		return (free_invalid_content(config, map));
	game->map->full_map = map;
	free_split(config);
	return (0);
}

int	read_file(char *map_file, t_game *game)
{
	char	*full_content;

	full_content = read_file_content(map_file);
	if (!full_content)
		return (-1);
	if (parser_file(full_content, game) == -1)
	{
		free(full_content);
		return (-1);
	}
	free(full_content);
	return (0);
}
