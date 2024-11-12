/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:44:53 by jco               #+#    #+#             */
/*   Updated: 2023/12/05 13:26:35 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int		ft_printf(const char *format, ...);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int n);
size_t	ft_strlen(const char *str);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbr_unsigned_hex(unsigned int n);
int		ft_putnbr_unsigned_hex_x(unsigned int n);
int		ft_putnbr_pointer(void *ptr);

#endif
