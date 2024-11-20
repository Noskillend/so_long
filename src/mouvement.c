/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 21:27:30 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/20 11:08:31 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int handle_keypress(int keycode, t_game *game)
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
		ft_printf("Exiting game via ESC...\n");
		destroy_game(game);
		exit(0);
	}
	return (0);
}


void move_player(t_game *game, int new_x, int new_y, char direction)
{
    char next_tile;

    // Met à jour l'image même si le mouvement est bloqué
    if (direction == 'W')
        game->current_player_img = game->player_img_up;
    else if (direction == 'A')
        game->current_player_img = game->player_img_left;
    else if (direction == 'S')
        game->current_player_img = game->player_img_down;
    else if (direction == 'D')
        game->current_player_img = game->player_img_right;

    next_tile = game->map[new_y][new_x];

    // Bloqué par un mur
    if (next_tile == '1') {
        render_map(game); // Redessine la map avec la nouvelle image
        return;
    }

    // Collecte un collectible
    if (next_tile == 'C') {
        game->collectibles--;
        ft_printf("Collectible picked up! Remaining: %d\n", game->collectibles);
    }

    // Gestion de la sortie
    if (next_tile == 'E') {
        if (game->collectibles == 0) {
            ft_printf("You won! Exiting game...\n");
            destroy_game(game);
            exit(0);
        } else {
            ft_printf("You need to collect all items first!\n");
            render_map(game); // Redessine la map avec la nouvelle image
            return;
        }
    }

    // Mise à jour de la position
    game->map[game->player_y][game->player_x] = '0';
    game->map[new_y][new_x] = 'P';
    game->player_x = new_x;
    game->player_y = new_y;

    // Incrémente les pas
    game->steps++;
    ft_printf("Steps: %d\n", game->steps);

    // Redessine la map
    render_map(game);
    ft_printf("Player moved to (%d, %d)\n", new_x, new_y);
}












// static void	handle_movement(int keycode, t_game *game)
// {
//     if (keycode == 13) // 'W' key
//         move_player(game, game->player_x, game->player_y - 1, 'U');
//     else if (keycode == 0) // 'A' key
//         move_player(game, game->player_x - 1, game->player_y, 'L');
//     else if (keycode == 1) // 'S' key
//         move_player(game, game->player_x, game->player_y + 1, 'D');
//     else if (keycode == 2) // 'D' key
//         move_player(game, game->player_x + 1, game->player_y, 'R');
// }

// static void	handle_exit(int keycode, t_game *game)
// {
// 	if (keycode == 53 || keycode == 65307) // 'ESC'
// 	{
// 		ft_printf("Exiting game...\n");
// 		destroy_game(game);
// 		exit(0);
// 	}
// }

// int	handle_keypress(int keycode, t_game *game)
// {
// 	handle_movement(keycode, game);
// 	handle_exit(keycode, game);
// 	return (0);
// }



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
				return;
			}
			x++;
		}
		y++;
	}
}



void	print_map(char **map, int height, int width)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
            ft_printf("%c", map[y][x]);
        ft_printf("\n");
    }
}

