/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 15:50:37 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/22 12:10:26 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*fct_check_realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*new;
	int		total;

	block = get_block(ptr);
	if (search_valide_block(ptr) == NULL)
		return (NULL);
	if (block->size >= size)
		return (block->data);
	if (block->size < size)
	{
		new = malloc(size);
		if (!new)
			return (NULL);
		total = (block->type == 2) ? (block->size - BLOCKSIZE) : block->size;
		ft_memcpy(new, block->data, total);
		free(ptr);
		return (new);
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	if (size == 0 && ptr)
		free(ptr);
	if (size <= 0)
		return (NULL);
	if (!ptr)
	{
		ptr = malloc(size);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	else
		return (fct_check_realloc(ptr, size));
	return (NULL);
}
