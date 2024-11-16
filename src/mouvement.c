/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:27:30 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/16 21:34:10 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_player(t_game *game, int new_x, int new_y)
{
	char	next_tile;

	next_tile = game->map[new_y][new_x];
	if (next_tile == '1')
		return ;
	if (next_tile == 'C')
		game->collectibles--;
	if (next_tile == 'E' && game->collectibles == 0)
	{
		ft_printf("You won! Exiting game...\n");
		destroy_game(game);
		exit(0);
	}
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	ft_printf("Player moved to (%d, %d)\n", new_x, new_y);
	render_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 13)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == 0)
		move_player(game, game->player_x - 1, game->player_y);
	else if (keycode == 1)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == 2)
		move_player(game, game->player_x + 1, game->player_y);
	else if (keycode == 53)
	{
		ft_printf("Exiting game...\n");
		destroy_game(game);
		exit(0);
	}
	return (0);
}

void	setup_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

