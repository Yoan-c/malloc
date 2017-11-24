/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:41:43 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:21 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block	*get_firs_memory(size_t size, int ctr)
{
	t_block	*block;

	ctr = check_size(size);
	if (ctr == 2)
		block = create_x_large_memory(size);
	else
	{
		block = create_first_memory(size);
		if (!block)
			return (NULL);
		split_block(block, size);
	}
	g_global_mem = block;
	return (block);
}

t_block	*get_memory(size_t size, int ctr)
{
	t_block	*block;

	if (ctr != -1)
	{
		ctr = check_size(size);
		if (ctr == 2)
		{
			block = create_x_large_memory(size);
		}
		else
			block = get_new_place(size, ctr);
		return (block);
	}
	else
		return (get_firs_memory(size, ctr));
	return (NULL);
}

void	*malloc(size_t size)
{
	t_block		*block;

	block = NULL;
	if (size <= 0)
		return (NULL);
	if (g_global_mem == NULL)
		block = get_memory(size, -1);
	else
		block = get_memory(size, 1);
	if (block)
		return (block->data);
	else
		return (NULL);
}
