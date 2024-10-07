/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 19:10:22 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/19 20:51:43 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		size;

	size = 0;
	if (lst == NULL)
		return (size);
	current = lst;
	while (current->next != NULL)
	{
		size++;
		current = current->next;
	}
	return (++size);
}
