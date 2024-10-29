/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/28 21:34:48 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int is_all_ones(char *line)
{
	int i = 0;

	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if (line[i] != '1' && !ft_isspace(line[i]))
			return -1;
		i++;
	}
	return (0);
}

int check_ones(char **lines, int size)
{
	int		i;
	char	*line;
	int		start;
	int		end;

	i = 0;
	if (is_all_ones(lines[0]) == -1 || is_all_ones(lines[size]) == -1)
		return (-1);
	while (i < size)
	{
		line = lines[i];
		start = 0;
		end = ft_strlen(line) - 1;
		while (start <= end && ft_isspace(line[start]))
			start++;
		while (end >= start && ft_isspace(line[end]))
			end--;
		if (line[start] != '1' || line[end] != '1')
			return (-1);
		i++;
	}
	return (0);
}

int check_walls_one(char **lines)
{
	int	i;

	i = 0;
	while (lines[i] != NULL)
		i++;
	if (check_ones(lines, i - 1) == -1)
		return (-1);
	return (0);
}
