/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:39:28 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/22 22:43:49 by ajuliao-         ###   ########.fr       */
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
	int i;

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
