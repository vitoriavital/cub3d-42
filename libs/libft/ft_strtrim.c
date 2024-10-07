/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:03:16 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/17 17:56:26 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start_idx;
	int		end_idx;
	int		final_size;
	char	*str;

	start_idx = 0;
	end_idx = ft_strlen(s1) - 1;
	final_size = 0;
	while (s1[start_idx] && ft_strchr(set, s1[start_idx]))
		start_idx++;
	while (end_idx > start_idx && ft_strchr(set, s1[end_idx]))
		end_idx--;
	if ((end_idx - start_idx) >= 0)
		final_size = end_idx - start_idx + 1;
	str = (char *)malloc((final_size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < final_size)
		str[i++] = s1[start_idx++];
	str[i] = '\0';
	return (str);
}
