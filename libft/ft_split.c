/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:20:33 by jco               #+#    #+#             */
/*   Updated: 2024/06/20 16:11:56 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

size_t	word_length(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

char	*al_copy(const char *s, size_t len)
{
	size_t	i;
	char	*dest;

	dest = malloc(sizeof(char) * (len + 1));
	if (dest != NULL)
	{
		i = 0;
		while (i < len)
		{
			dest[i] = s[i];
			i++;
		}
		dest[len] = '\0';
	}
	return (dest);
}

void	free_result(char **result, size_t word_count)
{
	while (word_count-- > 0)
		free(result[word_count]);
	free(result);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**result;

	if (!s)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !result)
		return (NULL);
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[count++] = al_copy(s, word_length(s, c));
			if (!result[count - 1])
				return (free_result(result, count - 1), NULL);
			s += word_length(s, c);
		}
		else
			s++;
	}
	result[count] = NULL;
	return (result);
}
