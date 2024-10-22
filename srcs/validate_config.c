/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/21 21:11:09 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

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

int	handle_file_check(char **file)
{
	if (ft_strncmp(file[0], "F", 1) == 0 || ft_strncmp(file[0], "C", 1) == 0)
	{
		if (check_c_f(file[1]) != 0)
		{
			free_split(file);
			return (-1);
		}
	}
	else if (check_file_dir(file[1]) != 0)
	{
		free_split(file);
		return (-1);
	}
	return (0);
}

int	check_config(char **line, t_game *game)
{
	char	**file;
	int		i;

	i = 0;
	while (line[i])
	{
		file = ft_split(line[i], ' ');
		if (!file[1] || file[2] != NULL)
		{
			free_split(file);
			return (-1);
		}
		if (handle_file_check(file) != 0)
			return (-1);
		free_split(file);
		i++;
	}
	set_config(line, game);
	return (0);
}