/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:28:47 by jco               #+#    #+#             */
/*   Updated: 2023/11/28 15:03:14 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_number_size(int n)
{
	unsigned int	temp;
	size_t			size;

	size = 0;
	temp = (unsigned int)(n);
	if (n == 0)
		size = 1;
	else
	{
		if (n < 0)
		{
			size++;
			temp = (unsigned int)(-n);
		}
		while (temp != 0)
		{
			temp /= 10;
			size++;
		}
	}
	return (size);
}

static void	fill_result(char *result, int n, size_t size)
{
	result[size] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n = -(n);
	}
	else
	{
		if (n == 0)
		{
			result[0] = '0';
			return ;
		}
	}
	while (size > 0)
	{
		size--;
		if (n == 0 && result[0] == '-')
		{
			result[size] = '-';
			break ;
		}
		result[size] = '0' + (n % 10);
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	size;

	if (n == -2147483648)
	{
		result = (char *)malloc(12);
		if (result == NULL)
			return (NULL);
		ft_strlcpy(result, "-2147483648", 12);
		return (result);
	}
	size = get_number_size(n);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	fill_result(result, n, size);
	return (result);
}
