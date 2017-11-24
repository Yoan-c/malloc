/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:51:33 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:12:33 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

int		show_alloc_mem_large(unsigned long total)
{
	t_block *block;
	int		b;

	b = 0;
	block = begin_global_memory();
	while (block && (block->type == 0 || block->type == 1))
		block = block->next;
	if (block && block->type == 2 && block->is_free == 0)
	{
		while (block)
		{
			if (block->type == 2 && block->is_free == 0)
			{
				if (b++ == 0)
					ft_printf("LARGE : %p \n", block);
				ft_printf("%p - %p : %d octets \n", block->data,
						(block->data + block->size), block->size);
				total += block->size;
			}
			block = block->next;
		}
	}
	return (total);
}

int		show_alloc_mem_small(unsigned long total)
{
	t_block *block;
	int		b;

	b = 0;
	block = begin_global_memory();
	while (block && block->type == 0)
		block = block->next;
	if (block && block->type == 1 && block->is_free == 0)
	{
		while (block)
		{
			if (block->type == 1 && block->is_free == 0)
			{
				if (b++ == 0)
					ft_printf("SMALL : %p \n", block);
				ft_printf("%p - %p : %d octets \n", block->data,
						(block->data + block->size), block->size);
				total += block->size;
			}
			block = block->next;
		}
	}
	return (total);
}

int		show_alloc_mem_tiny(unsigned long total)
{
	t_block *block;
	int		b;

	b = 0;
	block = begin_global_memory();
	if (block && block->type == 0)
	{
		while (block)
		{
			if (block->type == 0 && block->is_free == 0)
			{
				if (b++ == 0)
					ft_printf("TINY : %p \n", block);
				ft_printf("%p - %p : %d octets \n", block->data,
						(block->data + block->size), block->size);
				total += block->size;
			}
			block = block->next;
		}
	}
	return (total);
}

void	show_alloc_mem(void)
{
	unsigned long long	total;

	total = 0;
	total += show_alloc_mem_tiny(0);
	total += show_alloc_mem_small(0);
	total += show_alloc_mem_large(0);
	if (total > 0)
		ft_printf("TOTAL : %ld octets \n", total);
}
