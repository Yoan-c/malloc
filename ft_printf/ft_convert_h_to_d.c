/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_h_to_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 10:52:45 by ycoutena          #+#    #+#             */
/*   Updated: 2017/11/14 11:01:47 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

intmax_t	ft_convert_h_to_number(char *hexa)
{
	int			nb;
	int			total;
	int			i;
	int			j;
	static char	tab[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F'};

	j = 0;
	i = 0;
	total = 0;
	nb = ft_strlen(hexa);
	nb--;
	while (hexa[i])
	{
		j = 0;
		if (hexa[i] != '0')
			while (tab[j] && tab[j] != hexa[i])
				j++;
		total += (j * ft_power(16, nb));
		nb--;
		i++;
	}
	return (total);
}
