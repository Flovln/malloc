/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 14:31:12 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 09:27:49 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		size_type(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	else
		return (size);
}

size_t	calculate_chunk_size(size_t size)
{
	size_t chunk_size;

	if (size <= TINY)
		chunk_size = SIZECHUNK + (SIZEBLOCK * BLOCKS) + (TINY * BLOCKS);
	else if (size <= SMALL)
		chunk_size = SIZECHUNK + (SIZEBLOCK * BLOCKS) + (SMALL * BLOCKS);
	else
		chunk_size = SIZECHUNK + SIZEBLOCK + size;
	return (chunk_size);
}

size_t	calculate_page_size(size_t size)
{
	size_t	valid_size;
	size_t	page_size;
	size_t	nb_pages;

	page_size = getpagesize();
	nb_pages = size / page_size;
	if (nb_pages * page_size < size)
		valid_size = page_size * (nb_pages + 1);
	else
		valid_size = nb_pages * page_size;
	return (valid_size);
}

size_t	get_chunk_valid_size(size_t size)
{
	size_t raw_size;
	size_t valid_size;

	raw_size = calculate_chunk_size(size);
	valid_size = calculate_page_size(raw_size);
	return (valid_size);
}
