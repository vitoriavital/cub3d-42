/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavitori <mavitori@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:56:33 by mavitori          #+#    #+#             */
/*   Updated: 2023/10/20 16:20:02 by mavitori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int long n)
{
	int	counter;

	counter = 0;
	if (n < 0)
	{
		n *= -1;
		counter++;
	}
	while (n >= 10)
	{
		n = n / 10;
		counter++;
	}
	if (n < 10 && n >= 0)
		counter++;
	return (counter);
}

char	*ft_itoa(int n)
{
	char			*number;
	int				digits;
	int long		nbr;

	nbr = n;
	digits = count_digits(nbr);
	number = (char *)malloc((digits + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	number[digits--] = '\0';
	if (n < 0)
	{
		number[0] = '-';
		nbr *= -1;
	}
	else if (nbr == 0)
		number[0] = '0';
	while (nbr > 0)
	{
		number[digits] = (nbr % 10) + '0';
		nbr = nbr / 10;
		digits--;
	}
	return (number);
}
