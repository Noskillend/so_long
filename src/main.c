/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:03:03 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/20 11:20:47 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

int	handle_close(t_game *game)
{
	ft_printf("Exiting game via window close button...\n");
	destroy_game(game);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	ft_printf("Initializing game...\n");
	if (!init_game(&game, argv[1]))
	{
		ft_printf("Error: Failed to initialize the game.\n");
		return (1);
	}
	setup_player_position(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	return (0);
}
