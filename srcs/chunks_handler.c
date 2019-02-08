/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:19:36 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:37:55 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	init_chunk_blocks(t_chunk *chunk)
{
	t_block *block;
	int		i;

	i = 0;
	while (i < BLOCKS)
	{
		block = get_block_meta_data(chunk, i);
		block->size = 0;
		block->id = i;
		block->ptr = get_block_data(chunk, i);
		i++;
		if (chunk->type != TINY && chunk->type != SMALL)
			break ;
	}
}

t_chunk	*get_chunk(t_chunk **chunks, void *ptr)
{
	t_chunk *chunk;

	chunk = *chunks;
	while (chunk)
	{
		if (ptr > chunk->ptr && ptr < (chunk->ptr + chunk->size))
			return (chunk);
		chunk = chunk->next;
	}
	return (NULL);
}

t_chunk	*create_new_chunk(size_t size)
{
	t_chunk *chunk;
	void	*ptr;
	size_t	chunk_size;

	chunk_size = get_chunk_valid_size(size);
	ptr = mmap(0, chunk_size, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (ptr == MAP_FAILED)
		return (NULL);
	chunk = (t_chunk *)ptr;
	chunk->type = size_type(size);
	chunk->size = chunk_size;
	if (chunk->type <= SMALL)
		chunk->free = 100;
	else
		chunk->free = 1;
	chunk->ptr = ptr;
	chunk->next = NULL;
	init_chunk_blocks(chunk);
	return (chunk);
}

void	chunk_list_push_new(t_chunk **head, t_chunk *new_chunk)
{
	t_chunk	*cur;

	if (!*head)
	{
		*head = new_chunk;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_chunk;
}

t_chunk	*first_fit_chunk(t_chunk **chunks, size_t size)
{
	t_chunk	*chunk;

	chunk = *chunks;
	while (1)
	{
		if (chunk->type == size_type(size) && chunk->free > 0)
		{
			chunk->free -= 1;
			return (chunk);
		}
		if (chunk->next)
			chunk = chunk->next;
		else
			break ;
	}
	return (NULL);
}
