/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:22:05 by jco               #+#    #+#             */
/*   Updated: 2023/12/05 12:22:17 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_nb(long nb)
{
	if (nb >= 10)
	{
		write_nb(nb / 10);
		write_nb(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

int	ft_putnbr(int n)
{
	long	nb;
	int		len;

	nb = n;
	len = 0;
	if (nb == 0)
	{
		ft_putchar('0');
		return (1);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
		len++;
	}
	write_nb(nb);
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static int	ft_putnbr_recursive(unsigned int n)
{
	int	digit;
	int	len;

	if (n == 0)
		return (0);
	digit = n % 10;
	len = ft_putnbr_recursive(n / 10);
	ft_putchar(digit + '0');
	return (len + 1);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	return (ft_putnbr_recursive(n));
}
