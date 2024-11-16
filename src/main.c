/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 01:03:03 by noskillend        #+#    #+#             */
/*   Updated: 2024/11/16 16:46:37 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("Erorr: Invalid number of arguments.\n");
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		ft_putstr_fd("Error: Failed to initialize the game.\n", 2);
		return (1);
	}
	render_map(&game);
	mlx_loop(game.mlx);
	destroy_game(&game);
	return (0);
}
