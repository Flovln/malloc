/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 11:58:16 by fviolin           #+#    #+#             */
/*   Updated: 2015/12/02 14:14:06 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*s2;

	i = 0;
	d1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (i < n && (s2[i] != (unsigned char)c))
	{
		d1[i] = s2[i];
		i++;
	}
	if (s2[i] == (unsigned char)c)
	{
		d1[i] = s2[i];
		i++;
		return (d1 + i);
	}
	else
		return (NULL);
}
