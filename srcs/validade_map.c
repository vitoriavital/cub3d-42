/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/12 13:35:50 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

typedef enum e_configs	t_configs;
enum						e_configs
{
	NO = -6,
	SO = -5,
	WE = -4,
	EA = -3,
	F = -2,
	C = -1,
};

int	check_config_signal(char *line)
{
	// retirar espaços antes do caracter
	// checar os 3 primeiros
	if(ft_strncmp(line, "NO", 2) == 0)
		return (0);
	else if(ft_strncmp(line, "SO", 2) == 0)
		return (0);
	else if(ft_strncmp(line, "WE", 2) == 0)
		return (0);
	else if(ft_strncmp(line, "EA", 2) == 0)
		return (0);
	else if(ft_strncmp(line, "F", 1) == 0)
		return (0);
	else if(ft_strncmp(line, "C", 1) == 0)
		return (0);
	return (1);
}

void	print_teste(char **content)
{
	int i = 0;

	while(content[i])
	{
		printf("->%s\n", content[i++]);
	}
}

void	parser_file(char *full_content)
{
	char	*config[70000];
	char	*map[70000];
	char	**content;
	int		i;
	int		j;
	int		h;

	i = 0;
	j = 0;
	h = 0;
	content = ft_split(full_content, '\n'); //fazer split mesmo?
	while(content[i])
	{
		if(check_config_signal(content[i]) == 0)
		{
			//se for mandar pra config
			config[j] = ft_strdup(content[i]);
			j++;
		}
		else
		{
			map[h] = ft_strdup(content[i]);
			h++;
		}
		i++;
	}
	print_teste(config);
	printf("->>>>\n");
	print_teste(map);
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
	parser_file(full_content);
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
