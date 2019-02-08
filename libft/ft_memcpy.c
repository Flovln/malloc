/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:48:22 by fviolin           #+#    #+#             */
/*   Updated: 2015/12/09 15:54:53 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d1;
	unsigned char	*s2;

	i = 0;
	d1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	while (i < n)
	{
		d1[i] = s2[i];
		i++;
	}
	return (dst);
}
