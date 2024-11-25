/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:27:30 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 02:23:29 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == 119)
		move_player(game, game->player_x, game->player_y - 1, 'W');
	else if (keycode == 115)
		move_player(game, game->player_x, game->player_y + 1, 'S');
	else if (keycode == 97)
		move_player(game, game->player_x - 1, game->player_y, 'A');
	else if (keycode == 100)
		move_player(game, game->player_x + 1, game->player_y, 'D');
	else if (keycode == 65307)
	{
		destroy_game(game);
		exit(0);
	}
	return (0);
}

static void	update_player_image(t_game *game, char direction)
{
	if (direction == 'W')
		game->current_player_img = game->player_img_up;
	else if (direction == 'A')
		game->current_player_img = game->player_img_left;
	else if (direction == 'S')
		game->current_player_img = game->player_img_down;
	else if (direction == 'D')
		game->current_player_img = game->player_img_right;
}

static int	handle_next_tile(t_game *game, char next_tile)
{
	if (next_tile == '1')
		return (0);
	if (next_tile == 'C')
		game->collectibles--;
	if (next_tile == 'E')
	{
		if (game->collectibles == 0)
		{
			ft_printf("You won! Exiting game...\n");
			destroy_game(game);
			exit(0);
		}
		else
		{
			ft_printf("You need to collect all items first!\n");
			return (0);
		}
	}
	return (1);
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->steps++;
	ft_printf("Steps: %d\n", game->steps);
}

void	move_player(t_game *game, int new_x, int new_y, char direction)
{
	char	next_tile;

	update_player_image(game, direction);
	next_tile = game->map[new_y][new_x];
	if (!handle_next_tile(game, next_tile))
	{
		render_map(game);
		return ;
	}
	update_player_position(game, new_x, new_y);
	render_map(game);
}
