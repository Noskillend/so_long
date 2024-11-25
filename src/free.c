/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 01:24:55 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/25 17:34:09 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include "../minilibx/mlx.h"

void	free_copy(char **copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(copy[i++]);
	free(copy);
}

void	destroy_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

static void	destroy_images(t_game *game)
{
	if (game->floor_img)
		mlx_destroy_image(game->mlx, game->floor_img);
	if (game->wall_img)
		mlx_destroy_image(game->mlx, game->wall_img);
	if (game->player_img)
		mlx_destroy_image(game->mlx, game->player_img);
	if (game->player_img_up)
		mlx_destroy_image(game->mlx, game->player_img_up);
	if (game->player_img_down)
		mlx_destroy_image(game->mlx, game->player_img_down);
	if (game->player_img_left)
		mlx_destroy_image(game->mlx, game->player_img_left);
	if (game->player_img_right)
		mlx_destroy_image(game->mlx, game->player_img_right);
	if (game->c_img)
		mlx_destroy_image(game->mlx, game->c_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
}

static void	destroy_mlx(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	destroy_game(t_game *game)
{
	destroy_images(game);
	destroy_mlx(game);
	destroy_map(game->map);
	ft_bzero(game, sizeof(t_game));
}
