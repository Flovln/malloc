/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:40:36 by fviolin           #+#    #+#             */
/*   Updated: 2015/12/02 14:04:20 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *temp1;
	unsigned char *temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	while (*temp1 && *temp1 == *temp2)
	{
		temp1++;
		temp2++;
	}
	return (*temp1 - *temp2);
}
