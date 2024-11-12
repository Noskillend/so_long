/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:33:00 by jco               #+#    #+#             */
/*   Updated: 2023/12/05 13:26:56 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	conversion(va_list args, const char format)
{
	int	len;

	len = 0;
	if (format == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		len += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		len += ft_putnbr_unsigned_hex(va_arg(args, unsigned int));
	else if (format == 'X')
		len += ft_putnbr_unsigned_hex_x(va_arg(args, unsigned int));
	else if (format == '%')
		len += ft_putchar('%');
	else if (format == 'p')
		len += ft_putnbr_pointer(va_arg(args, void *));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	int		len;
	int		i;
	va_list	args;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			len += conversion(args, format[i]);
		}
		else
		{
			write (1, &format[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
