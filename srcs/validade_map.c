/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validade_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:03:19 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/10/12 12:55:06 by ajuliao-         ###   ########.fr       */
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
		// if(content[i][0] == 'NO' || content[i][0] == 'SO'
		//  || content[i][0] == 'WE' || content[i][0] == 'EA' || content[i][0] == 'F'
		//  || content[i][0] == 'C' )
	return (0);
}

void	parser_file(char *full_content)
{
	char	**config;
	char	**content;
	char	**map;
	int		i;
	int		j;

	content = ft_split(full_content, '\n'); //fazer split mesmo?
	while(content[i]) // checar se não é o map tbm
	{
		// if(check_config_signal(content[i]))
			//se for mandar pra config
		i++;
	}

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
