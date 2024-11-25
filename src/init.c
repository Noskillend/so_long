/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 02:30:36 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 17:41:48 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

void	init_struct(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
}

static int	load_environment_images(t_game *game, int *width, int *height)
{
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/sol.xpm",
			width, height);
	if (!game->floor_img)
		return (0);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/bush.xpm",
			width, height);
	if (!game->wall_img)
		return (0);
	game->c_img = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm",
			width, height);
	if (!game->c_img)
		return (0);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			width, height);
	if (!game->exit_img)
		return (0);
	return (1);
}

static int	load_player_images(t_game *game, int *width, int *height)
{
	game->player_img = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_down.xpm", width, height);
	if (!game->player_img)
		return (0);
	game->player_img_up = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_back.xpm", width, height);
	if (!game->player_img_up)
		return (0);
	game->player_img_down = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_down.xpm", width, height);
	if (!game->player_img_down)
		return (0);
	game->player_img_left = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_left.xpm", width, height);
	if (!game->player_img_left)
		return (0);
	game->player_img_right = mlx_xpm_file_to_image(game->mlx,
			"textures/perso_right.xpm", width, height);
	if (!game->player_img_right)
		return (0);
	game->current_player_img = game->player_img_down;
	return (1);
}

int	initialize_images(t_game *game, int *width, int *height)
{
	if (!load_environment_images(game, width, height))
		return (0);
	if (!load_player_images(game, width, height))
		return (0);
	return (1);
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
