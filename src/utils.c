/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:20:05 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 03:16:31 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

int	open_file(const char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		ft_printf("Error: Unable to open the map file.\n");
	return (fd);
}

void	print_map(char **map, int height, int width)
{
	int	y;
	int	x;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_printf("%c", map[y][x]);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

int	count_remaining_elem(char **map, int height, int width, char element)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == element)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

char	**duplicate_map(t_game *game)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < game->map_height)
	{
		copy[y] = ft_strdup(game->map[y]);
		if (!copy[y])
		{
			free_copy(copy, y);
			return (NULL);
		}
		y++;
	}
	copy[game->map_height] = NULL;
	return (copy);
}
