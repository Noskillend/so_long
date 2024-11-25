/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:33:36 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 02:33:57 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

int	flood_fill(t_flood *data, int x, int y)
{
	int	count;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (0);
	if (data->map[y][x] == '1' || data->map[y][x] == 'V')
		return (0);
	if (data->map[y][x] == 'E' && data->target == 'C')
		return (0);
	count = 0;
	if (data->map[y][x] == data->target)
		count++;
	data->map[y][x] = 'V';
	count += flood_fill(data, x + 1, y);
	count += flood_fill(data, x - 1, y);
	count += flood_fill(data, x, y + 1);
	count += flood_fill(data, x, y - 1);
	return (count);
}

int	can_reach_exit_after_collecting(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'E')
		return (1);
	map[y][x] = 'V';
	return (can_reach_exit_after_collecting(map, x + 1, y, game)
		|| can_reach_exit_after_collecting(map, x - 1, y, game)
		|| can_reach_exit_after_collecting(map, x, y + 1, game)
		|| can_reach_exit_after_collecting(map, x, y - 1, game));
}
