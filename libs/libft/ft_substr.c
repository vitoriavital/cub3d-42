/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:00:19 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/17 14:55:47 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	char	*substr;
	size_t	i;

	size = 0;
	if (start <= ft_strlen(s))
	{
		while (s[start + size] && (size + 1) <= len)
			size++;
	}
	substr = (char *) malloc((size + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
