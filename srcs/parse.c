/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/21 19:43:16 by ajuliao-         ###   ########.fr       */
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


int	read_file(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	char	*full_content;
	char	*temp;

	fd = open(map_file, O_RDONLY);
	if (fd < 1)
	{
		printf("Error: File error or not exist.\n");
		return (-1);
	}
	full_content = ft_strdup("");
	while(1)
	{
		line = get_next_line(fd);
		if(!line)
			break ;
		temp = full_content;
		full_content = ft_strjoin(full_content, line);
		free(line);
		free(temp);
	}
	if (parser_file(full_content, game) == -1)
	{
		free (full_content);
		return (-1);
	}
	free(full_content);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (-1);
	return 0;
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

int parser_file(char *full_content, t_game *game)
{
	char	**config;
	char	**map;
	char	**map_fill;
	char	**content;
	int		i;

	i = 0;
	content = ft_split(full_content, '\n');
	if (!content[0])
	{
		free_split(content);
		return (-1);
	}
	while ((check_config_signal(content[i]) == 0))
		i++;
	if (i != 6)
	{
		free_split(content);
		return (-1);
	}
	config = (char **)ft_calloc(sizeof(char *), 7);
	while (content[i])
		i++;
	map = (char **)ft_calloc(sizeof(char *), (i - 5));
	map_fill = (char **)ft_calloc(sizeof(char *), (i - 5));
	if (split_content(content, config, map, map_fill) == -1)
	{
		printf("Error: .\n");
		free(map);
		free_split(map_fill);
		free_split(config);
		return (-1);
	}
	if (check_config(config) == -1)
	{
		printf("Error: Invalid config.\n");
		free_split(map);
		free_split(map_fill);
		free_split(config);
		return (-1);
	}
	game->map_fill = map_fill;
	if (check_map(map, game) == -1)
	{
		printf("Error: Invalid map.\n");
		free_split(map);
		free_split(config);
		return (-1);
	}
	set_config(config, game);
	// printf("     \n");
	// printf("X-> %d\n Y-> %d\n",game->player->line, game->player->column);
	// print_teste(map);
	// printf("     \n");
	game->map->full_map = map;
	free_split(config);
	return (0);
}

