/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:05:25 by mavitori          #+#    #+#             */
/*   Updated: 2024/09/11 11:58:42 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			word_count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word_count);
}

static char	*build_word(char const *str, char c)
{
	int		i;
	int		size;
	char	*word;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	size = i + 1;
	word = (char *)malloc(size * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (str[i] != c && str[i])
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	clean(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free (array);
	return (1);
}

static int	build_array(char **array, const char *s, char c, int *j)
{
	char	*word;

	while (*s)
	{
		if (((*s == c) || (*s != c)) && *s)
		{
			while (*s == c)
				s++;
			if (*s != '\0')
			{
				word = build_word(&*s, c);
				if (word != NULL)
				{
					array[(*j)++] = word;
					s += ft_strlen(word);
				}
				else
					return (clean(array));
			}
		}
		else
			s++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		words;
	char	**array;

	j = 0;
	words = count_words(s, c);
	array = ft_calloc((words + 1), sizeof(char *));
	if (array == NULL)
		return (NULL);
	if (words > 0)
	{
		if (build_array(array, s, c, &j) == 1)
			array = NULL;
	}
	return (array);
}
