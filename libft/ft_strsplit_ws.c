/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 11:04:13 by fviolin           #+#    #+#             */
/*   Updated: 2016/03/18 11:48:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(char const *s)
{
	int cmp;
	int	i;

	cmp = 0;
	i = 0;
	while (*s)
	{
		if (i == 1 && ft_isspace(*s))
			i = 0;
		if (i == 0 && !ft_isspace(*s))
		{
			i = 1;
			cmp++;
		}
		s++;
	}
	return (cmp);
}

static int		ft_nstr(char const *s)
{
	int	len;

	len = 0;
	while (*s && !ft_isspace(*s))
	{
		s++;
		len++;
	}
	return (len);
}

char			**ft_strsplit_ws(char const *s)
{
	char	**t;
	int		i;
	int		word_nb;

	if (!s)
		return (NULL);
	i = 0;
	word_nb = ft_count(s);
	t = (char **)malloc(sizeof(char *) * (ft_count(s) + 1));
	if (t == NULL)
		return (NULL);
	while (word_nb--)
	{
		while (*s && ft_isspace(*s))
			s++;
		t[i] = ft_strsub((const char *)s, 0, ft_nstr(s));
		if (t[i] == NULL)
			return (NULL);
		s = s + ft_nstr(s);
		i++;
	}
	t[i] = NULL;
	return (t);
}
