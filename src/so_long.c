/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:38:09 by jco               #+#    #+#             */
/*   Updated: 2024/11/25 02:36:28 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

static int	find_player_position(t_game *game, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == 'P')
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	validate_collectibles(t_game *game, char **copy, int px, int py)
{
	t_flood	data;
	int		total_collectibles;
	int		reached_collectibles;

	data.map = copy;
	data.width = game->map_width;
	data.height = game->map_height;
	data.target = 'C';
	total_collectibles = count_remaining_elements(game->map,
			game->map_height, game->map_width, 'C');
	reached_collectibles = flood_fill(&data, px, py);
	return (reached_collectibles == total_collectibles);
}

static int	validate_exit(t_game *game, char **copy, int px, int py)
{
	t_flood	data;
	int		exit_reachable;

	data.map = copy;
	data.width = game->map_width;
	data.height = game->map_height;
	data.target = 'E';
	exit_reachable = flood_fill(&data, px, py);
	return (exit_reachable);
}

static int	validate_elements(t_game *game, int player_x, int player_y)
{
	char	**copy;

	copy = duplicate_map(game);
	if (!copy || !validate_collectibles(game, copy, player_x, player_y))
	{
		ft_printf("Error: Not all collectibles are reachable.\n");
		free_copy(copy, game->map_height);
		return (0);
	}
	free_copy(copy, game->map_height);
	copy = duplicate_map(game);
	if (!copy || !validate_exit(game, copy, player_x, player_y))
	{
		ft_printf("Error: Exit is not reachable.\n");
		free_copy(copy, game->map_height);
		return (0);
	}
	free_copy(copy, game->map_height);
	return (1);
}

int	is_map_playable(t_game *game)
{
	char	**copy;
	int		player_x;
	int		player_y;

	copy = duplicate_map(game);
	if (!copy || !find_player_position(game, &player_x, &player_y))
	{
		free_copy(copy, game->map_height);
		ft_printf("Error: Player position not found.\n");
		return (0);
	}
	free_copy(copy, game->map_height);
	return (validate_elements(game, player_x, player_y));
}
