/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fviolin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 11:28:58 by fviolin           #+#    #+#             */
/*   Updated: 2017/09/13 13:57:46 by fviolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <sys/mman.h>
# include <pthread.h>

# define SIZECHUNK sizeof(t_chunk)
# define SIZEBLOCK sizeof(t_block)
# define BLOCKS 100
# define TINY 1024
# define SMALL 4096

pthread_mutex_t		g_lock;

typedef struct		s_block
{
	int				size;
	void			*ptr;
	int				id;
}					t_block;

typedef struct		s_chunk
{
	int				type;
	size_t			size;
	void			*ptr;
	int				free;
	struct s_chunk	*next;
}					t_chunk;

/*
 ** Main functions
*/
void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

/*
 ** Utilities
*/
t_chunk				*static_hub(t_chunk *first);
int					size_type(size_t size);
size_t				get_chunk_valid_size(size_t size);
size_t				calculate_chunk_size(size_t size);
size_t				calculate_page_size(size_t size);
t_block				*get_block_meta_data(t_chunk *chunk, int id);
t_block				*get_block_data(t_chunk *chunk, int id);
t_chunk				*first_fit_chunk(t_chunk **chunk, size_t size);
void				*first_fit_block(t_chunk *chunk, size_t size);
void				chunk_list_push_new(t_chunk **head, t_chunk *new_chunk);
t_chunk				*create_new_chunk(size_t size);
int					check_free_blocks(t_chunk *chunks, size_t size);
t_chunk				*get_chunk(t_chunk **chunk, void *ptr);
void				free_blocks(t_chunk *chunk, void *ptr);
void				free_chunk(t_chunk **chunks);
void				free_empty_chunk(t_chunk **chunks);
void				free_blocks(t_chunk *chunks, void *ptr);
#endif
