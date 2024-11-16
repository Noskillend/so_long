/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:06:46 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/16 21:21:46 by noskillend       ###   ########.fr       */
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
	while(game->map[i])
	{
		if((int)ft_strlen(game->map[i]) != game->map_width)
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

int check_required_elements(t_game *game)
{
	int	x;
	int	y;
	int	player;
	int	exit;
	int	collectible;

	player = 0;
	exit = 0;
	collectible = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
				player++;
			else if (game->map[y][x] == 'E')
				exit++;
			else if (game->map[y][x] == 'C')
				collectible++;
			x++;
		}
		y++;
	}
	if (player != 1 || exit != 1 || collectible < 1)
	{
		ft_printf("Error: Map is missing required elements.\n");
		return (0);
	}
	return (1);
}

int validate_map(t_game *game)
{
	if (!game->map || game->map_width <= 0 || game->map_height <= 0)
	{
		ft_printf("Error: Invalid map dimensions or map not loaded.\n");
		return (0);
	}
	if (!check_valid_characters(game))
		return (0);
	if (!check_rectangular(game))
		return (0);
	if (!check_surrounded_by_walls(game))
		return (0);
	if (!check_required_elements(game))
		return (0);
	if (!is_map_playable(game))
		return (0);
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


char	**load_map(const char *map_path, int *width, int *height)
{
	int		fd;
	int		lines;
	char	**map;
	char	*line;
	int		i;

	lines = count_lines(map_path);
	if (lines <= 0 || !(map = malloc(sizeof(char *) * (lines + 1))))
		return (NULL);
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < lines && (line = get_next_line(fd)))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		map[i++] = line;
	}
	map[i] = NULL;
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

	if (!map)
		return ;
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	is_valid_extension(const char *filename, const char *ext)
{
	int	filename_len;
	int	ext_len;

	if(!filename || !ext)
		return (0);
	filename_len = ft_strlen(filename);
	ext_len = ft_strlen(ext);
	if (filename_len <= ext_len)
		return (0);
	return (ft_strncmp(filename + filename_len - ext_len, ext, ext_len) == 0);
}
