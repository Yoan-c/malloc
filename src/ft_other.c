/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:57:21 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:05 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block	*verif_place(size_t size, int ctr)
{
	t_block *block;

	block = g_global_mem;
	while (block)
	{
		if (block->is_free == 1 && block->type == ctr
				&& block->size >= (size + BLOCKSIZE))
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_block	*extend_memory(size_t size, int ctr)
{
	t_block *block;

	block = NULL;
	if (ctr == 0)
		block = create_tiny_memory(size);
	else if (ctr == 1)
		block = create_small_memory(size);
	else
		ft_putendl("ERREUR ");
	return (block);
}

t_block	*get_new_place(size_t size, int ctr)
{
	t_block		*block;

	block = verif_place(size, ctr);
	if (block)
	{
		split_block(block, size);
		return (block);
	}
	else
	{
		block = extend_memory(size, ctr);
		return (block);
	}
	return (NULL);
}

t_block	*get_large_block(size_t size)
{
	t_block					*block;
	unsigned long long		size_alloc;
	int						tot;

	tot = 0;
	size_alloc = (size + sizeof(t_block));
	block = NULL;
	while ((size_alloc + tot) % getpagesize() != 0)
		tot++;
	size_alloc += tot;
	block = (t_block *)mmap(0, size_alloc, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if ((unsigned long)block != 0xffffffffffffffff)
	{
		block->size = size_alloc;
		block->next = NULL;
		block->prev = NULL;
		block->is_free = 0;
		block->type = check_size(size);
	}
	else
		block = NULL;
	return (block);
}
