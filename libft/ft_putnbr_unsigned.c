/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:13:03 by jco               #+#    #+#             */
/*   Updated: 2023/12/05 13:22:15 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base_recursive_u(unsigned long n, const char *base)
{
	int	digit;
	int	len;

	if (n == 0)
		return (0);
	digit = n % ft_strlen(base);
	len = ft_putnbr_base_recursive_u(n / ft_strlen(base), base);
	ft_putchar(base[digit]);
	return (len + 1);
}

int	ft_putnbr_unsigned_u(unsigned int n)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	return (ft_putnbr_base_recursive_u(n, "0123456789"));
}

int	ft_putnbr_unsigned_hex(unsigned int n)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		return (ft_putnbr_base_recursive_u(n, "0123456789abcdef"));
}

int	ft_putnbr_unsigned_hex_x(unsigned int n)
{
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	else
		return (ft_putnbr_base_recursive_u(n, "0123456789ABCDEF"));
}

int	ft_putnbr_pointer(void *ptr)
{
	unsigned long long	ptr_val;

	ptr_val = (unsigned long long)ptr;
	if (ptr == NULL)
	{
		ft_putstr("(nil)");
		return (5);
	}
	else
	{
		ft_putstr("0x");
		return (ft_putnbr_base_recursive_u(ptr_val, "0123456789abcdef") + 2);
	}
}
