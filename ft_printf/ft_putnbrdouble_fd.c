/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrdouble_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycoutena <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 09:13:16 by ycoutena          #+#    #+#             */
/*   Updated: 2017/10/03 09:16:41 by ycoutena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbrdouble_fd(double num, int fd)
{
	int		n;
	int		nb;

	n = num;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	nb = num;
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		if (n == -2147483648)
			ft_putstr_fd("2147483648", fd);
		else
			ft_putchar_fd(nb + '0', fd);
	}
}
