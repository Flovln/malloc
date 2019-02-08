/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:22:31 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 16:54:34 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(char const *s, char c)
{
	int cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			cmp++;
		}
		s++;
	}
	return (cmp);
}

static int		ft_nstr(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**t;
	int		i;
	int		word_nb;

	if (!s)
		return (NULL);
	i = 0;
	word_nb = ft_count(s, c);
	t = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (t == NULL)
		return (NULL);
	while (word_nb--)
	{
		while (*s && *s == c)
			s++;
		t[i] = ft_strsub((const char *)s, 0, ft_nstr(s, c));
		if (t[i] == NULL)
			return (NULL);
		s = s + ft_nstr(s, c);
		i++;
	}
	t[i] = NULL;
	return (t);
}
