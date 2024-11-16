/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:38:09 by jco               #+#    #+#             */
/*   Updated: 2024/11/16 21:41:00 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

int	init_game(t_game *game, const char *map_path)
{
	int	width;
	int	height;

	game->map = load_map(map_path, &game->map_width, &game->map_height);
	if (!game->map)
		return (0);
	if (!is_valid_extension(map_path, ".ber"))
		return (0);
	if (!validate_map(game))
		return (0);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
		game->map_height * TILE_SIZE, "so_long");
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/sol.xpm", &width, &height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/bush.xpm", &width, &height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/perso_centre.xpm", &width, &height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
	if (!game->floor_img || !game->wall_img || !game->player_img
		|| !game->collectible_img || !game->exit_img)
		return (0);
	return (1);
}

void	destroy_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->floor_img);
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->player_img);
	mlx_destroy_image(game->mlx, game->collectible_img);
	mlx_destroy_image(game->mlx, game->exit_img);
	destroy_map(game->map);
}

int	flood_fill(char **map, int x, int y, t_game *game, char target)
{
	int	count;

	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'E' && target == 'C')
		return (0);
	count = 0;
	if (map[y][x] == target)
		count++;
	map[y][x] = 'V';
	count += flood_fill(map, x + 1, y, game, target);
	count += flood_fill(map, x - 1, y, game, target);
	count += flood_fill(map, x, y + 1, game, target);
	count += flood_fill(map, x, y - 1, game, target);
	return (count);
}


int	can_reach_exit_after_collecting(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	// Ignorez les cases non marchables ou déjà visitées
	if (map[y][x] == '1' || map[y][x] == 'V') // 'V' pour Visité
		return (0);

	// Si on atteint la sortie, c'est valide
	if (map[y][x] == 'E')
		return (1);

	// Marquez la case comme visitée
	map[y][x] = 'V';

	// Explorez dans les 4 directions
	return (can_reach_exit_after_collecting(map, x + 1, y, game)
		|| can_reach_exit_after_collecting(map, x - 1, y, game)
		|| can_reach_exit_after_collecting(map, x, y + 1, game)
		|| can_reach_exit_after_collecting(map, x, y - 1, game));
}


int	count_remaining_elements(char **map, int height, int width, char element)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == element)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	is_map_playable(t_game *game)
{
	char	**copy;
	int		player_x = -1;
	int		player_y = -1;
	int		y;

	// Étape 1 : Faire une copie de la carte
	copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!copy)
		return (0);
	y = 0;
	while (y < game->map_height)
	{
		copy[y] = ft_strdup(game->map[y]);
		y++;
	}
	copy[y] = NULL;

	// Étape 2 : Trouver la position du joueur
	y = 0;
	while (y < game->map_height)
	{
		int	x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				player_x = x;
				player_y = y;
				break ;
			}
			x++;
		}
		y++;
	}

	if (player_x == -1 || player_y == -1)
	{
		ft_printf("Error: Player position not found.\n");
		return (0);
	}

	// Étape 3 : Vérifiez que tous les collectibles sont atteignables
	int collectibles_count = count_remaining_elements(game->map, game->map_height, game->map_width, 'C');
	int reached_collectibles = flood_fill(copy, player_x, player_y, game, 'C');
	if (reached_collectibles != collectibles_count)
	{
		ft_printf("Error: Not all collectibles are reachable.\n");
		return (0);
	}

	// Étape 4 : Réinitialiser la copie pour vérifier la sortie
	y = 0;
	while (y < game->map_height)
	{
		free(copy[y]);
		copy[y] = ft_strdup(game->map[y]);
		y++;
	}
	copy[y] = NULL;

	// Étape 5 : Vérifiez que la sortie est atteignable après avoir collecté tous les collectibles
	int exit_reachable = flood_fill(copy, player_x, player_y, game, 'E');
	if (exit_reachable == 0)
	{
		ft_printf("Error: Exit is not reachable after collecting all collectibles.\n");
		return (0);
	}

	// Libérer la mémoire
	y = 0;
	while (y < game->map_height)
		free(copy[y++]);
	free(copy);

	return (1);
}


