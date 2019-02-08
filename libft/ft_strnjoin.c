/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/11 16:17:35 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/10 10:44:28 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = ft_strnew(ft_strlen(s1) + (ft_strlen(s2) * len) + 1);
	if (s)
	{
		ft_strcat(s, s1);
		while (i < len)
		{
			ft_strcat(s, s2);
			i++;
		}
	}
	return (s);
}
