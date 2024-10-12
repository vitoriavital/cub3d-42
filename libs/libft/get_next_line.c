/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajuliao- <ajuliao-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:47:21 by ajuliao-          #+#    #+#             */
/*   Updated: 2023/12/09 10:51:19 by ajuliao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_one_line(t_list_get **list)
{
	char	*str;

	if (!list)
		return (NULL);
	str = malloc(str_len(list) + 1);
	if (str == NULL)
	{
		free(str);
		return (NULL);
	}
	copy_txt(list, str);
	return (str);
}

void	dealloc_list(t_list_get **list)
{
	t_list_get	*temp;

	if (list)
	{
		while (*list)
		{
			temp = *list;
			*list = (*list)->next;
			free(temp);
		}
	}
	temp = NULL;
}

void	create_list(t_list_get **list, int fd)
{
	char	*str;
	int		i;

	i = 1;
	while (!find_n(list) && i > 0)
	{
		str = malloc(BUFFER_SIZE + 1);
		if (!str)
		{
			free(str);
			return ;
		}
		i = read(fd, str, BUFFER_SIZE);
		if (i < 0 || (!*list && i == 0))
		{
			dealloc_list(list);
			free(str);
			return ;
		}
		str[i] = '\0';
		i = 0;
		while (str[i] != '\0')
			insert_end(list, str[i++]);
		free(str);
	}
}

char	*get_next_line(int fd)
{
	static t_list_get	*list;
	char			*txt;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		dealloc_list(&list);
		return (NULL);
	}
	create_list(&list, fd);
	if (!list)
		return (NULL);
	txt = get_one_line(&list);
	if (!txt)
	{
		free(txt);
		return (NULL);
	}
	return (txt);
}
