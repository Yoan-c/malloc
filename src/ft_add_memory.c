/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add__memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 08:16:14 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:46 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	add_tiny_memory(t_block *block, t_block *tmp, t_block *new)
{
	if (block)
	{
		if (tmp != block && (block->type == 1 || block->type == 2))
		{
			new->next = block;
			new->prev = tmp;
			tmp->next = new;
		}
		else if (tmp == block && tmp->prev == NULL)
		{
			new->next = tmp;
			new->prev = NULL;
			tmp->prev = new;
			g_global_mem = new;
		}
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	add_small(t_block *block, t_block *tmp, t_block *new)
{
	if (block)
	{
		if (tmp != block && block->type == 2)
		{
			new->next = block;
			new->prev = tmp;
			tmp->next = new;
		}
		else if (tmp == block && tmp->prev == NULL)
		{
			new->prev = NULL;
			new->next = tmp;
			tmp->prev = new;
			g_global_mem = new;
		}
	}
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
}

void	add_small_memory(t_block *block, t_block *new)
{
	t_block *tmp;

	tmp = block;
	while (block && block->type == 1)
	{
		tmp = block;
		block = block->next;
	}
	add_small(block, tmp, new);
}
