/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:49:40 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:43 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free_large(t_block *block)
{
	t_block	*tmp;
	int		check;

	g_global_mem = begin_global_memory();
	if (g_global_mem == block)
	{
		g_global_mem = block->next;
		if (block->next)
			block->next->prev = NULL;
	}
	else
	{
		tmp = block->prev;
		tmp->next = block->next;
		if (block->next)
			block->next->prev = tmp;
	}
	check = munmap(block, (block->size));
	if (check != 0)
		ft_putendl("ERROR Memory delete ");
}

void	fusion_block(t_block *block)
{
	if (block)
	{
		if (block->next && block->next->is_free == 1)
		{
			block->size += block->next->size + BLOCKSIZE;
			block->next = block->next->next;
			if (block->next)
				block->next->prev = block;
		}
	}
}

void	free(void *ptr)
{
	t_block *block;

	if (ptr)
	{
		if (g_global_mem)
		{
			block = get_block(ptr);
			if (block && search_valide_block(ptr))
			{
				block->is_free = 1;
				if (block->type == 2)
					free_large(block);
				else
					fusion_block(block);
			}
		}
	}
}
