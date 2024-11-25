/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:03:03 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 18:40:20 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

int	handle_close(t_game *game)
{
	destroy_game(game);
	exit(0);
	return (0);
}

int	validate_map_and_extension(t_game *game, const char *map_path)
{
	if (!is_valid_extension(map_path, ".ber"))
	{
		ft_printf("Error: Invalid map extension.\n");
		return (0);
	}
	game->map = load_map(map_path, &game->map_width, &game->map_height);
	if (!game->map)
	{
		ft_printf("Error: Failed to load map.\n");
		return (0);
	}
	if (!validate_map(game))
	{
		ft_printf("Error: Map structure is invalid.\n");
		destroy_map(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}

int	init_game(t_game *game, const char *map_path)
{
	init_struct(game);
	if (!validate_map_and_extension(game, map_path))
		return (0);
	if (!is_map_playable(game))
	{
		ft_printf("Error: Map is not playable.\n");
		return (0);
	}
	game->steps = 0;
	if (!initialize_window_and_images(game))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Error: Invalid number of arguments.\n");
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		ft_printf("Error: Failed to initialize the game.\n");
		destroy_game(&game);
		return (1);
	}
	setup_player_position(&game);
	render_map(&game);
	mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
