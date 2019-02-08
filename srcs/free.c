/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:37:02 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:46:52 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_empty_chunk(t_chunk **head)
{
	t_chunk *prev;
	t_chunk *next;
	t_chunk *cur;

	prev = NULL;
	cur = *head;
	pthread_mutex_lock(&g_lock);
	while (cur)
	{
		if (cur->type > SMALL && cur->free == 1)
		{
			if (!prev)
			{
				*head = cur->next;
				static_hub(*head);
			}
			else
				prev->next = cur->next;
			munmap(cur, cur->size);
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	pthread_mutex_unlock(&g_lock);
}

void	free_blocks(t_chunk *chunk, void *ptr)
{
	t_block *block;
	int		i;

	i = 0;
	while (i < BLOCKS)
	{
		block = get_block_meta_data(chunk, i);
		if (chunk->type <= SMALL && block->ptr == ptr)
		{
			block->size = 0;
			chunk->free++;
		}
		else if (chunk->type > SMALL && block->ptr == ptr)
		{
			block->size = 0;
			chunk->free = 1;
			break ;
		}
		i++;
	}
}

void	free(void *ptr)
{
	t_chunk *chunks;
	t_chunk *chunk;

	chunks = static_hub(NULL);
	chunk = get_chunk(&chunks, ptr);
	if (!chunk || !ptr)
		return ;
	pthread_mutex_lock(&g_lock);
	free_blocks(chunk, ptr);
	pthread_mutex_unlock(&g_lock);
	free_empty_chunk(&chunks);
}
