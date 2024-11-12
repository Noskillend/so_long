/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:26:46 by jco               #+#    #+#             */
/*   Updated: 2023/11/28 15:00:06 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1)
		return (NULL);
	while (is_in_set(*s1, set))
		s1++;
	len = ft_strlen(s1) - 1;
	while (is_in_set(s1[len], set))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
