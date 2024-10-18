/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/18 19:57:42 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	print_teste(char **content)
{
	int i;

	i = -1;
	while(content[++i])
	{
		printf("->%s\n", content[i]);
	}
}

// typedef enum e_configs	t_configs;
// enum						e_configs
// {
// 	NO = -6,
// 	SO = -5,
// 	WE = -4,
// 	EA = -3,
// 	F = -2,
// 	C = -1,
// };

void	free_split(char **content)
{
	int i;

	i = -1;
	while(content[i])
	{
		free(content[++i]);
	}
	free(content);
}

int	check_rgb(char *red, char *green, char *blue)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(red);
	g = ft_atoi(green);
	b = ft_atoi(blue);
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	return (0);
}

int	check_directions(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(&file[len - 4], ".png", 4) != 0)
		return (-1);
	return (0);
}

int check_c_f(char *rgb)
{
	char	**colors;

	colors = ft_split(rgb, ',');
	if (colors[3] != NULL)
	{
		free_split(colors);
		return (-1);
	}
	if (check_rgb(colors[0], colors[1], colors[2]) != 0)
	{
		free_split(colors);
		return (-1);
	}
	free_split(colors);
	return (0);
}

void	set_config(char **config,t_game *game)
{
	int		i;
	char	**split_line;

	i = 0;
	while (i < 6)
	{
		split_line = ft_split(config[i], ' ');
		if (ft_strncmp(split_line[0], "NO", 2) == 0)
			game->map->north_texture = ft_strdup(split_line[1]);
		else if (ft_strncmp(split_line[0], "SO", 2) == 0)
			game->map->south_texture = ft_strdup(split_line[1]);
		else if (ft_strncmp(split_line[0], "WE", 2) == 0)
			game->map->west_texture = ft_strdup(split_line[1]);
		else if (ft_strncmp(split_line[0], "EA", 2) == 0)
			game->map->east_texture = ft_strdup(split_line[1]);
		else if (ft_strncmp(split_line[0], "F", 1) == 0)
			game->map->floor_color = ft_strdup(split_line[1]);
		else if (ft_strncmp(split_line[0], "C", 1) == 0)
			game->map->ceiling_color = ft_strdup(split_line[1]);
		free_split(split_line);
		i++;
	}
}
int		ft_mtxlen(char	**matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
		i++;
	return (i);
}

char	**find_space(char **map)
{
	char	**result;
	int		i;
	int		j;

	j = -1;
	i = ft_mtxlen(map);
	result = (char **)malloc(sizeof(char *) * (i + 1));
	while (map[++j])
	{
		result[j] = ft_strdup(map[j]);
		free(map[j]);
	}
	result[j] = '\0';
	return(result);

}

int	check_walls(char **lines)
{
	int	line;
	int	column;
	int	i;
	int	j;

	i = 0;
	line = ft_mtxlen(lines);

}

void	count_player(char c, int *player)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player)++;
	return ;
}

void	set_position(char **map, t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	x = 0;
	y = 0;
	while(map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'W')
			{
				game->player->line = i;
				game->player->column = j;
			}
			j++;
		}
		i++;
	}
}


int	check_map(char **lines, t_game *game)
{
	int		i;
	int		line;
	int		player;

	line = 0;
	i = 0;
	player = 0;
	// verificar catacteres
	while(lines[line])
	{
		while(lines[line][i])
		{
			if(ft_strrchr(" 01NSWE", lines[line][i]) == NULL)
				return(-1);
			count_player(lines[line][i], &player);
			i++;
		}
		line++;
		i = 0;
	}
	if (player != 1)
		return (-1);
	set_position(lines, game);

	// verificar paredes
	// if (check_walls(lines) == -1)
	// 	return (-1);
	//substituir espaços por 1 ou 0
	// map = find_space(lines);
	// print_teste(map);
	// mandar pro flood fill

}

int	check_config(char **line)
{
	char	**file;
	int		i;

	i = 0;
	while (line[i])
	{
		file = ft_split(line[i], ' ');
		if (!file[1])
		{
			free_split(file);
			return (-1);
		}
		if (file[2] != NULL)
		{
			free_split(file);
			return (-1);
		}
		if (ft_strncmp(file[0], "F", 1) == 0 || ft_strncmp(file[0], "C", 1) == 0)
		{
			if (check_c_f(file[1]) != 0)
			{
				free_split(file);
				return (-1);
			}
		}
		else if (check_directions(file[1]) != 0)
		{
			free_split(file);
			return (-1);
		}
		free_split(file);
		i++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (-1);
	return 0;
}

int	check_config_signal(char *line)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (0);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (0);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (0);
	return (-1);
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
		free(content[i]);
		i++;
	}
	config[j] = NULL;
	map[h] = NULL;
	map_fill[h] = NULL;
	return (0);
}

void parser_file(char *full_content, t_game *game)
{
	char	**config;
	char	**map;
	char	**map_fill;
	char	**content;
	int		i;

	i = 0;
	content = ft_split(full_content, '\n');
	while((check_config_signal(content[i]) == 0))
		i++;
	if ( i != 6)
		exit(0);
	config = (char **)malloc(sizeof(char *) * 7);
	while (content[i])
		i++;
	map = (char **)malloc(sizeof(char *) * (i - 6));
	if (split_content(content, config, map, map_fill) == -1)
	{
		printf("Error: .\n");
		exit(0);
	}
	if (check_config(config) == -1)
	{
		printf("Error: Invalid config.\n");
		exit(0);
	}
	if (check_map(map, game) == -1)
	{
		printf("Error: Invalid map.\n");
		exit(0);
	}
	set_config(config, game);
	// print_teste(config);
	printf("     \n");
	// set_position(map, game);
	printf("X-> %d\n Y-> %d\n",game->player->line, game->player->column);
	print_teste(map);
	printf("     \n");
	game->map_fill = map_fill;
	print_teste(game->map_fill);
	// set_map(map, game);
	exit(0);
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
	parser_file(full_content, game);
	free(full_content);
	return (0);
}

int verify_extension(char *map_file)
{
	int			len;
	const char	*extension=".cub";

	len = 0;
	while(map_file[len])
		len++;
	if(ft_strncmp(&map_file[len - 4], ".cub", 4) == 0)
		return (0);
	printf("Error: The file need be .cub\n");
	return (-1);
}
