/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:56:32 by mavitori          #+#    #+#             */
/*   Updated: 2024/11/04 14:54:05 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

int	error_parser(char *text, char **config)
{
	if (config != NULL)
		free_split(config);
	if (text)
		printf("Error: %s\n", text);
	return (-1);
}

static int	check_all_spaces(char *content, int j)
{
	while (content[j])
	{
		if (!ft_isspace(content[j]))
			return (-1);
		j++;
	}
	return (0);
}

static int	check_new_line(char c)
{
	if (c == '\n')
		return (1);
	else
		return (0);
}

int	check_spaces(char *content)
{
	int	i;
	int	map_started;
	int	last_was_newline;
	int	j;

	map_started = 0;
	last_was_newline = 1;
	i = 0;
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
