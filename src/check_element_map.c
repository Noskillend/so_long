/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 00:48:44 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 02:19:57 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

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
