/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/11/02 16:55:45 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int	verify_extension(char *map_file)
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

void	replace_tabs(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '\t')
			content[i] = ' ';
		i++;
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (-1);
	return (0);
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
	replace_tabs(full_content);
	if (parser_file(full_content, game) == -1)
	{
		free(full_content);
		return (error_parser("Check the map", NULL));
		// return (-1);
	}
	free(full_content);
	return (0);
}
