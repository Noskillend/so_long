/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:06:46 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/23 22:14:16 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

int	is_valid_element(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

int	check_valid_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (!is_valid_element(game->map[y][x]))
			{
				ft_printf("Error: Invalid character in map.\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_rectangular(t_game *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
		{
			ft_printf("Error: Map is not rectangular.\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_surrounded_by_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1' || game->map[game->map_height - 1][x] != '1')
		{
			ft_printf("Error: Map is not surrounded by walls.\n");
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1' || game->map[y][game->map_width - 1] != '1')
		{
			ft_printf("Error: Map is not surrounded by walls.\n");
			return (0);
		}
		y++;
	}
	return (1);
}

int	count_elements(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
		game->collectibles++;
	else if (game->map[y][x] == 'P')
		game->player_count++;
	else if (game->map[y][x] == 'E')
		game->exit_count++;
	return (1);
}

int	check_required_elements(t_game *game)
{
	int	x;
	int	y;

	game->collectibles = 0;
	game->player_count = 0;
	game->exit_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			count_elements(game, x, y);
			x++;
		}
		y++;
	}
	if (game->player_count != 1 || game->exit_count != 1
		|| game->collectibles < 1)
	{
		ft_printf("Error: Map is missing required elements.\n");
		return (0);
	}
	return (1);
}

int	validate_map(t_game *game)
{
	ft_printf("Checking map characters...\n");
	if (!check_valid_characters(game))
	{
		ft_printf("Error: Invalid characters in map.\n");
		return (0);
	}

	ft_printf("Checking map rectangle...\n");
	if (!check_rectangular(game))
	{
		ft_printf("Error: Map is not rectangular.\n");
		return (0);
	}

	ft_printf("Checking map walls...\n");
	if (!check_surrounded_by_walls(game))
	{
		ft_printf("Error: Map is not surrounded by walls.\n");
		return (0);
	}

	ft_printf("Checking required elements...\n");
	if (!check_required_elements(game))
	{
		ft_printf("Error: Map is missing required elements.\n");
		return (0);
	}

	return (1);
}



int	count_lines(const char *path)
{
	int		fd;
	int		lines;
	char	buffer[1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while (read(fd, buffer, 1) > 0)
	{
		if (buffer[0] == '\n')
			lines++;
	}
	close(fd);
	return (lines + 1);
}

char	**allocate_map(int lines)
{
	char	**map;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	return (map);
}

int	open_file(const char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_printf("Error: Unable to open the map file.\n");
	return (fd);
}

char	*read_and_trim_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
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
		if (!line)
			break ;
		map[i++] = line;
	}
	map[i] = NULL;
	return (i);
}

char	**load_map(const char *map_path, int *width, int *height)
{
	int		fd;
	int		lines;
	int		i;
	char	**map;

	lines = count_lines(map_path);
	if (lines <= 0)
		return (NULL);
	map = allocate_map(lines);
	if (!map)
		return (NULL);
	fd = open_file(map_path);
	if (fd < 0)
		return (NULL);
	i = fill_map(map, fd, lines);
	close(fd);
	if (i == 0)
	{
		free(map);
		return (NULL);
	}
	*width = ft_strlen(map[0]);
	*height = lines;
	return (map);
}

void	destroy_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	is_valid_extension(const char *filename, const char *ext)
{
	int	filename_len;
	int	ext_len;

	if (!filename || !ext)
		return (0);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len <= ext_len)
		return (0);
	return (ft_strncmp(filename + filename_len - ext_len, ext, ext_len) == 0);
}
