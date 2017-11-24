/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_memory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:45:20 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:49 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block	*create_tiny_memory(size_t size)
{
	t_block *block;
	t_block *tmp;
	t_block *new;

	new = create_first_memory(size);
	if (!new)
		return (NULL);
	block = begin_global_memory();
	tmp = block;
	while (block && block->type == 0)
	{
		tmp = block;
		block = block->next;
	}
	add_tiny_memory(block, tmp, new);
	split_block(new, size);
	return (new);
}

t_block	*create_small_memory(size_t size)
{
	t_block *block;
	t_block *new;
	t_block *tmp;

	new = create_first_memory(size);
	if (!new)
		return (NULL);
	block = begin_global_memory();
	while (block && block->type == 0)
	{
		tmp = block;
		block = block->next;
	}
	if (block)
		add_small_memory(block, new);
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
	split_block(new, size);
	return (new);
}

t_block	*create_x_large_memory(size_t size)
{
	t_block *block;
	t_block *new;
	t_block *tmp;

	new = get_large_block(size);
	if (!new)
		return (NULL);
	block = begin_global_memory();
	tmp = block;
	while (block && block->next)
		block = block->next;
	if (block)
	{
		block->next = new;
		new->prev = block;
	}
	else
		g_global_mem = new;
	return (new);
}

t_block	*create_first_memory(size_t size)
{
	t_block	*block;
	int		size_alloc;
	int		tot;

	tot = 0;
	size_alloc = (size + sizeof(t_block)) * 100;
	while ((size_alloc + tot) % getpagesize() != 0)
		tot++;
	size_alloc += tot;
	block = NULL;
	block = mmap(0, size_alloc, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if ((unsigned long)block != 0xffffffffffffffff)
	{
		block->size = size_alloc;
		block->size_total = size_alloc;
		block->next = NULL;
		block->prev = NULL;
		block->is_free = 1;
		block->type = check_size(size);
	}
	else
		block = NULL;
	return (block);
}
