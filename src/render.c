/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:07:41 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 03:09:46 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

static void	render_tile(t_game *game, int x, int y)
{
	int	pos_x;
	int	pos_y;

	pos_x = x * TILE_SIZE;
	pos_y = y * TILE_SIZE;
	mlx_put_image_to_window(game->mlx, game->win,
		game->floor_img, pos_x, pos_y);
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win,
			game->wall_img, pos_x, pos_y);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win,
			game->collectible_img, pos_x, pos_y);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win,
			game->exit_img, pos_x, pos_y);
	else if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win,
			game->current_player_img, pos_x, pos_y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y);
			x++;
		}
		y++;
	}
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
