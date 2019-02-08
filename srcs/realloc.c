/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 10:37:12 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:39:24 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*reallocate_block(t_chunk *chunk, void *ptr, size_t size)
{
	t_block *block;
	void	*new;
	int		i;

	i = 0;
	while (i < BLOCKS)
	{
		block = get_block_meta_data(chunk, i);
		if (block->ptr == ptr)
		{
			if (size_type(size) == chunk->type)
			{
				block->size = size;
				return (block->ptr);
			}
			new = malloc(size);
			pthread_mutex_lock(&g_lock);
			ft_memcpy(new, block->ptr, block->size);
			free_blocks(chunk, ptr);
			pthread_mutex_unlock(&g_lock);
			return (new);
		}
		i++;
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	t_chunk *chunks;
	t_chunk	*chunk;
	t_block	*block;
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (!size && ptr)
		return (malloc(TINY));
	chunks = static_hub(NULL);
	chunk = get_chunk(&chunks, ptr);
	if (!chunk)
		return (NULL);
	new = reallocate_block(chunk, ptr, size);
	if (new)
		free_empty_chunk(&chunks);
	return (new);
}
