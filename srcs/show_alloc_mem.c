/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:11:25 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 11:23:34 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	print_hexa(unsigned long addr)
{
	const char *hex;

	hex = "0123456789abcdef";
	if (addr >= 16)
	{
		print_hexa(addr / 16);
		print_hexa(addr % 16);
	}
	else
		ft_putchar(hex[addr]);
}

static void	print_memory_addr(void *mem)
{
	ft_putstr("0x");
	print_hexa((unsigned long)mem);
}

static int	print_tiny_small_chunks(t_chunk *chunk)
{
	t_block *block;
	int		blocks_bytes_sum;
	int		i;

	i = 0;
	blocks_bytes_sum = 0;
	while (i < BLOCKS)
	{
		block = get_block_meta_data(chunk, i);
		if (block->size)
		{
			print_memory_addr(block->ptr);
			ft_putstr(" - ");
			print_memory_addr(block->ptr + block->size);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putstr(" octets\n");
		}
		i++;
		blocks_bytes_sum += block->size;
	}
	return (blocks_bytes_sum);
}

static int	print_blocks(t_chunk *chunk)
{
	t_block *block;
	int		total;

	total = 0;
	if (chunk->type > SMALL)
	{
		block = get_block_meta_data(chunk, 0);
		print_memory_addr(block->ptr);
		ft_putstr(" - ");
		print_memory_addr(block->ptr + block->size);
		ft_putstr(" : ");
		ft_putnbr(block->size);
		ft_putstr(" octets\n");
		total += block->size;
	}
	else if (chunk->type <= SMALL)
		total += print_tiny_small_chunks(chunk);
	return (total);
}

void		show_alloc_mem(void)
{
	t_chunk *chunks;
	t_chunk	*chunk;
	int		bytes_sum;

	chunks = static_hub(NULL);
	chunk = chunks;
	bytes_sum = 0;
	while (chunk)
	{
		if (chunk->type == TINY)
			ft_putstr("TINY : ");
		else if (chunk->type == SMALL)
			ft_putstr("SMALL : ");
		else if (chunk->type > SMALL)
			ft_putstr("LARGE : ");
		print_memory_addr(chunk->ptr);
		ft_putchar('\n');
		bytes_sum += print_blocks(chunk);
		chunk = chunk->next;
	}
	ft_putstr("Total : ");
	ft_putnbr(bytes_sum);
	ft_putstr(" octets\n");
}
