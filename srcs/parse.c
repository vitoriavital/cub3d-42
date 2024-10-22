/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/22 09:29:11 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int verify_extension(char *map_file)
{
	int	len;

	len = 0;
	while (map_file[len])
		len++;
	if (ft_strncmp(&map_file[len - 4], ".cub", 4) == 0)
		return (0);
	printf("Error: The file need be .cub\n");
	return (-1);
}

char	*read_file_content(char *map_file)
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

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (-1);
	return (0);
}

int	split_content(char **content, char **config, char **map, char **map_fill)
{
	int		i;
	int		j;
	int		h;

	i = 0;
	j = 0;
	h = 0;
	while(content[i])
	{
		if(check_config_signal(content[i]) == 0)
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

int	handle_config_validation(char **content)
{
	int i;

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

int	parser_file(char *full_content, t_game *game)
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
	map = (char **)ft_calloc(sizeof(char *), (i - 5));
	map_fill = (char **)ft_calloc(sizeof(char *), (i - 5));
	split_content(content, config, map, map_fill);
	game->map_fill = map_fill;
	if (check_config(config, game) == -1 || check_map(map, game) == -1)
	{
		printf("Error: Invalid content.\n");
		free_split(config);
		free_split(map);
		return (-1);
	}
	game->map->full_map = map;
	free_split(config);
	return (0);
}
	// printf("     \n");
	// printf("X-> %d\n Y-> %d\n",game->player->line, game->player->column);
	// print_teste(map);
	// printf("     \n");
