/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:30:36 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 02:32:26 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

void	init_struct(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
}

int	initialize_images(t_game *game, int *width, int *height)
{
	game->floor_img = mlx_xpm_file_to_image(game->mlx,
			"textures/sol.xpm", width, height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx,
			"textures/bush.xpm", width, height);
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_down.xpm", width, height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", width, height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", width, height);
	game->player_img_up = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_back.xpm", width, height);
	game->player_img_down = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_down.xpm", width, height);
	game->player_img_left = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_left.xpm", width, height);
	game->player_img_right = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_right.xpm", width, height);
	game->current_player_img = game->player_img_down;
	return (game->floor_img && game->wall_img && game->player_img
		&& game->collectible_img && game->exit_img
		&& game->player_img_up && game->player_img_down
		&& game->player_img_left && game->player_img_right);
}

int	initialize_window_and_images(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx,
			game->map_width * TILE_SIZE, game->map_height * TILE_SIZE,
			"so_long");
	if (!game->win || !initialize_images(game, &width, &height))
	{
		destroy_game(game);
		return (0);
	}
	return (1);
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
