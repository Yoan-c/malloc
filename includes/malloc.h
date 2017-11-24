/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 07:48:43 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/24 10:05:18 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MALLOC_H
#	define MALLOC_H
#	include "../ft_printf/includes/ft_printf.h"
#	include <sys/mman.h>
#	include <errno.h>
#	define PAGE getpagesize()
#	define TINY getpagesize() * 8
#	define SMALL getpagesize() * 32
#	define BLOCKSIZE sizeof(struct s_block)

typedef struct				s_block
{
	unsigned long long		size;
	unsigned long long		size_total;
	int						type;
	int						is_free;
	void					*ptr;
	struct s_block			*prev;
	struct s_block			*next;
	char					data[1];
}							t_block;

extern	void				*g_global_mem;
void						free(void *ptr);
void						*malloc(size_t size);
void						*realloc(void *ptr, size_t size);
void						show_alloc_mem();
t_block						*get_new_place(size_t size, int ctr);
t_block						*create_first_memory(size_t size);
t_block						*create_x_large_memory(size_t size);
t_block						*verif_place(size_t size, int ctr);
t_block						*extend_memory(size_t size, int ctr);
t_block						*get_large_block(size_t size);
t_block						*begin_global_memory(void);
int							check_size(size_t size);
void						split_block(t_block *block, size_t size);
t_block						*get_block(void *ptr);
t_block						*create_tiny_memory(size_t size);
t_block						*create_small_memory(size_t size);
void						add_tiny_memory(t_block *b, t_block *t, t_block *n);
void						add_small_memory(t_block *bl, t_block *n);
t_block						*search_valide_block(void *block);

#	endif
