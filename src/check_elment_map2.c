/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elment_map2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:19:11 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 02:20:07 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

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

int	validate_map(t_game *game)
{
	if (!check_no_empty_lines(game))
		return (0);
	if (!check_valid_characters(game))
		return (0);
	if (!check_rectangular(game))
		return (0);
	if (!check_surrounded_by_walls(game))
		return (0);
	if (!check_required_elements(game))
		return (0);
	return (1);
}

int	check_no_empty_lines(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		if (ft_strlen(game->map[y]) == 0)
		{
			ft_printf("Error: Map contains an empty line.\n");
			return (0);
		}
		y++;
	}
	return (1);
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
