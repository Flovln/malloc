/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:17:12 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:45:36 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block	*get_block_data(t_chunk *chunk, int id)
{
	if (chunk->type == TINY)
	{
		return (t_block *)(chunk->ptr + SIZECHUNK +
				(SIZEBLOCK * BLOCKS) + (TINY * id));
	}
	if (chunk->type == SMALL)
	{
		return (t_block *)(chunk->ptr + SIZECHUNK +
				(SIZEBLOCK * BLOCKS) + (SMALL * id));
	}
	return (t_block *)(chunk->ptr + SIZECHUNK + SIZEBLOCK);
}

t_block	*get_block_meta_data(t_chunk *chunk, int id)
{
	if (chunk->type == TINY || chunk->type == SMALL)
		return (t_block *)(chunk->ptr + SIZECHUNK + (SIZEBLOCK * id));
	return (t_block *)(chunk->ptr + SIZECHUNK);
}

int		check_free_blocks(t_chunk *chunks, size_t size)
{
	if (chunks)
	{
		while (1)
		{
			if (chunks->type == size_type(size) && chunks->free > 0)
				return (0);
			if (chunks->next)
				chunks = chunks->next;
			else
				break ;
		}
	}
	return (1);
}

void	*first_fit_block(t_chunk *chunk, size_t size)
{
	t_block	*block;
	void	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (!chunk)
		return (NULL);
	while (i < BLOCKS)
	{
		block = get_block_meta_data(chunk, i);
		if (!block->size)
		{
			block->size = size;
			ptr = block->ptr;
			break ;
		}
		i++;
	}
	return (ptr);
}
