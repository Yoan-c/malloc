/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 08:12:17 by ycoutena          #+#    #+#             */
/*   Updated: 2017/10/03 09:26:11 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_check_nb(double nb)
{
	if (nb < 0)
		nb = nb * -1;
	return (nb);
}

void	ft_putdouble_fd(double nb, int precision, int fd)
{
	int		i;
	double	nb2;
	int		k;

	i = (int)nb;
	ft_putnbrdouble_fd(nb, fd);
	nb = nb - i;
	ft_putchar_fd('.', fd);
	nb = ft_check_nb(nb);
	if (precision < 1)
		precision = 1;
	while (precision >= 1)
	{
		nb = nb * 10;
		nb2 = nb;
		k = nb;
		nb2 = nb - k;
		nb2 = nb2 * 10;
		i = (int)nb;
		if (nb2 > 9)
			i++;
		ft_putnbrdouble_fd(i, fd);
		nb = nb - i;
		precision--;
	}
}
