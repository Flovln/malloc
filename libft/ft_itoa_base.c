/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 12:46:17 by fviolin           #+#    #+#             */
/*   Updated: 2016/02/15 12:58:10 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_convert(int nb, char *s, int base, int i)
{
	int			j;
	const char	letter[16] = "0123456789ABCDEF";

	j = 0;
	if (nb < 0)
	{
		if (base == 10)
		{
			s[j] = '-';
			j++;
		}
		nb = -nb;
	}
	i = 1;
	while (nb / i > base - 1)
		i = i * base;
	while (i != 0)
	{
		s[j] = letter[nb / i];
		nb = nb % i;
		i = i / base;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char			*ft_itoa_base(int value, int base)
{
	int		i;
	int		count;
	char	*s;

	if (value == -2147483648)
		return (ft_strdup("-2147483648"));
	else
	{
		count = 0;
		i = value;
		while (i > 0)
		{
			count++;
			i = i / base;
		}
		s = (char *)malloc(sizeof(char) * count + 1);
		s = ft_convert(value, s, base, 0);
		return (s);
	}
}
