/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:53:18 by jco               #+#    #+#             */
/*   Updated: 2024/06/18 13:38:14 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_new_line(char *line)
{
	size_t	count;
	char	*temp;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (NULL);
	temp = ft_substr_gnl(line, count + 1, ft_strlen_gnl(line) - count);
	if (*temp == '\0')
	{
		free(temp);
		temp = NULL;
	}
	line[count + 1] = '\0';
	return (temp);
}

static char	*read_and_stash(int fd, char *buffer, char *temp)
{
	int		read_bytes;
	char	*stash;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (0);
		else if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		if (!temp)
			temp = ft_strdup_gnl("");
		stash = temp;
		temp = ft_strjoin_gnl(stash, buffer);
		free(stash);
		stash = NULL;
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static char		*temp[MAX_FD];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_and_stash(fd, buffer, temp[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	temp[fd] = extract_new_line(line);
	return (line);
}
