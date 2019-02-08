/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:18:32 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:39:48 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	test_func(t_chunk **chunks)
{
	t_chunk *cur;

	cur = *chunks;
	if (!cur || !*chunks)
	{
		ft_putstr("Empty list");
		return ;
	}
	while (cur)
	{
		ft_putstr("cur->type : ");
		ft_putnbr(cur->type);
		ft_putchar('\n');
		ft_putstr("cur->free : ");
		ft_putnbr(cur->free);
		ft_putchar('\n');
		cur = cur->next;
	}
}

t_chunk	*static_hub(t_chunk *first)
{
	static t_chunk	*chunks = NULL;

	if (first)
	{
		pthread_mutex_init(&g_lock, NULL);
		chunks = first;
	}
	return (chunks);
}

void	*malloc(size_t size)
{
	t_chunk	*chunks;
	t_chunk *available;
	void	*ptr;

	if ((int)size < 0)
		return (NULL);
	chunks = static_hub(NULL);
	if (!chunks)
		chunks = static_hub(create_new_chunk(size));
	pthread_mutex_lock(&g_lock);
	if (check_free_blocks(chunks, size))
		chunk_list_push_new(&chunks, (create_new_chunk(size)));
	available = first_fit_chunk(&chunks, size);
	ptr = first_fit_block(available, size);
	pthread_mutex_unlock(&g_lock);
	return (ptr);
}
