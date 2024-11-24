/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:06:46 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 17:27:45 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

char	**allocate_map(int lines)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i <= lines)
	{
		map[i] = NULL;
		i++;
	}
	return (map);
}

char	*read_and_trim_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	if (line && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int	fill_map(char **map, int fd, int lines)
{
	int		i;
	char	*line;

	i = 0;
	while (i < lines)
	{
		line = read_and_trim_line(fd);
		if (!line || ft_strlen(line) == 0)
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			while (i > 0)
			{
				free(map[--i]);
				map[i] = NULL;
			}
			return (0);
		}
		map[i++] = line;
	}
	map[i] = NULL;
	return (1);
}

char	**load_map(const char *map_path, int *width, int *height)
{
	int		fd;
	int		lines;
	char	**map;

	lines = count_lines(map_path);
	if (lines <= 0)
		return (NULL);
	map = allocate_map(lines);
	if (!map)
		return (NULL);
	fd = open_file(map_path);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	if (!fill_map(map, fd, lines))
	{
		destroy_map(map);
		return (close(fd), NULL);
	}
	close(fd);
	*width = ft_strlen(map[0]);
	*height = lines;
	return (map);
}

int	is_map_length_valid(t_game *game)
{
	int	y;

	y = 0;
	while (game->map[y])
	{
		if ((int)ft_strlen(game->map[y]) > MAX_MAP_WIDTH)
		{
			ft_printf("Error: Line exceeds %d columns.\n", MAX_MAP_WIDTH);
			return (0);
		}
		y++;
	}
	if (y > MAX_MAP_HEIGHT)
	{
		ft_printf("Error: Map exceeds %d rows.\n", MAX_MAP_HEIGHT);
		return (0);
	}
	return (1);
}
