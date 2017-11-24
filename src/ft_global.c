/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_global.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:53:38 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:33 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block	*begin_global_memory(void)
{
	t_block *block;
	t_block *tmp;

	if (g_global_mem)
	{
		block = g_global_mem;
		if (block)
		{
			tmp = block;
			while (block && block->prev)
			{
				tmp = block;
				block = block->prev;
			}
			g_global_mem = block;
			if (block)
				return (block);
			else
				return (tmp);
		}
	}
	return (NULL);
}

int		check_size(size_t size)
{
	if (size > (size_t)SMALL)
	{
		return (2);
	}
	else if (size < (size_t)TINY)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

void	split_block(t_block *block, size_t size)
{
	t_block *new;

	new = (void *)(block->data + size);
	new->size = block->size - size - BLOCKSIZE;
	new->next = block->next;
	new->prev = block;
	new->is_free = 1;
	new->type = block->type;
	block->next = new;
	block->is_free = 0;
	block->size = size;
	block->size_total = size + BLOCKSIZE;
}

t_block	*search_valide_block(void *block)
{
	t_block	*tmp;

	tmp = begin_global_memory();
	while (tmp)
	{
		if (tmp->data == block)
			return (block);
		tmp = tmp->next;
	}
	return (NULL);
}

t_block	*get_block(void *ptr)
{
	t_block	*tmp;

	tmp = begin_global_memory();
	while (tmp)
	{
		if (tmp->data == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
