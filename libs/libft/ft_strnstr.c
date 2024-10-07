/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:04:11 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/20 16:23:47 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		j;
	char	*str;

	i = 0;
	str = (char *)big;
	if (little[i] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == little[j]
			&& little[j] && (i + j) < len)
		{
			j++;
		}
		if (little[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (0);
}
