/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:47:59 by ajuliao-          #+#    #+#             */
/*   Updated: 2024/11/04 15:26:52 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	insert_end(t_list_get **root, char value)
{
	t_list_get	*new_t_list;
	t_list_get	*curr;

	new_t_list = malloc(sizeof(t_list_get));
	if (new_t_list == NULL)
		return ;
	new_t_list->content = value;
	new_t_list->next = NULL;
	if (*root == NULL)
	{
		*root = new_t_list;
		return ;
	}
	curr = *root;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new_t_list;
}

size_t	find_n(t_list_get **list)
{
	t_list_get	*curr;

	curr = *list;
	while (curr)
	{
		if (curr->content == '\n')
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	copy_txt(t_list_get **list, char *str)
{
	int			i;
	t_list_get	*temp;

	i = 0;
	while (*list && (*list)->content != '\n')
	{
		str[i++] = (*list)->content;
		temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	if (*list && (*list)->content == '\n')
	{
		str[i++] = (*list)->content;
		temp = *list;
		*list = (*list)->next;
		free(temp);
	}
	str[i] = '\0';
}

size_t	str_len(t_list_get **list)
{
	size_t		len;
	t_list_get	*curr;

	if (!list || !*list)
		return (0);
	len = 0;
	curr = *list;
	while (curr && curr->content != '\n' )
	{
		curr = curr->next;
		len++;
	}
	return (++len);
}
