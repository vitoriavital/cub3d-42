/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:16:24 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/17 14:21:19 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destination;
	unsigned const char	*source;

	destination = (unsigned char *)dest;
	source = (unsigned const char *)src;
	if (destination == source)
		return (destination);
	if (destination < source)
	{
		i = -1;
		while (++i < n)
			destination[i] = source[i];
	}
	else
	{
		i = n + 1;
		while (--i > 0)
			destination[i - 1] = source[i - 1];
	}
	return (dest);
}
