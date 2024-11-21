/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:38:09 by jco               #+#    #+#             */
/*   Updated: 2024/11/21 22:07:34 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"

void	init_struct(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
}

int	validate_map_and_extension(t_game *game, const char *map_path)
{
    ft_printf("Validating map extension...\n");
    if (!is_valid_extension(map_path, ".ber"))
    {
        ft_printf("Error: Invalid map extension.\n");
        return (0);
    }

    ft_printf("Loading map...\n");
    game->map = load_map(map_path, &game->map_width, &game->map_height);
    if (!game->map)
    {
        ft_printf("Error: Failed to load map.\n");
        return (0);
    }

    ft_printf("Validating map structure...\n");
    if (!validate_map(game))
    {
        ft_printf("Error: Map structure is invalid.\n");
        return (0);
    }

    return (1);
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
	return (game->floor_img && game->wall_img && game->player_img &&
		game->collectible_img && game->exit_img &&
		game->player_img_up && game->player_img_down &&
		game->player_img_left && game->player_img_right);
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

int	init_game(t_game *game, const char *map_path)
{
	init_struct(game);
	if (!validate_map_and_extension(game, map_path))
		return (0);
	ft_printf("Checking if map is playable...\n");
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


void	destroy_game(t_game *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
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
	if (game->collectible_img)
		mlx_destroy_image(game->mlx, game->collectible_img);
	if (game->exit_img)
		mlx_destroy_image(game->mlx, game->exit_img);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	destroy_map(game->map);
}

int	flood_fill(t_flood *data, int x, int y)
{
	int	count;

	if (x < 0 || y < 0 || x >= data->width || y >= data->height)
		return (0);
	if (data->map[y][x] == '1' || data->map[y][x] == 'V')
		return (0);
	if (data->map[y][x] == 'E' && data->target == 'C')
		return (0);
	count = 0;
	if (data->map[y][x] == data->target)
		count++;
	data->map[y][x] = 'V';
	count += flood_fill(data, x + 1, y);
	count += flood_fill(data, x - 1, y);
	count += flood_fill(data, x, y + 1);
	count += flood_fill(data, x, y - 1);
	return (count);
}


int	can_reach_exit_after_collecting(char **map, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == 'E')
		return (1);
	map[y][x] = 'V';
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

void	free_copy(char **copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free(copy[i++]);
	free(copy);
}

int	is_map_playable(t_game *game)
{
	char	**copy;
	t_flood	data;
	int		player_x = -1;
	int		player_y = -1;
	int		total_collectibles;
	int		reached_collectibles;
	int		exit_reachable;

	// Dupliquer la carte
	ft_printf("Duplicating map for validation...\n");
	copy = malloc(sizeof(char *) * (game->map_height + 1));
	if (!copy)
		return (0);
	for (int y = 0; y < game->map_height; y++)
	{
		copy[y] = ft_strdup(game->map[y]);
		if (!copy[y])
		{
			free_copy(copy, y);
			ft_printf("Error: Failed to duplicate map.\n");
			return (0);
		}
	}
	copy[game->map_height] = NULL;

	// Trouver la position du joueur
	ft_printf("Finding player position...\n");
	for (int y = 0; y < game->map_height; y++)
	{
		for (int x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == 'P')
			{
				player_x = x;
				player_y = y;
				break ;
			}
		}
	}
	if (player_x == -1 || player_y == -1)
	{
		ft_printf("Error: Player position not found.\n");
		free_copy(copy, game->map_height);
		return (0);
	}

	// Vérification des collectibles
	ft_printf("Validating collectibles...\n");
	data.map = copy;
	data.width = game->map_width;
	data.height = game->map_height;
	data.target = 'C';
	total_collectibles = count_remaining_elements(game->map, game->map_height, game->map_width, 'C');
	reached_collectibles = flood_fill(&data, player_x, player_y);
	ft_printf("Total collectibles: %d, Reached: %d\n", total_collectibles, reached_collectibles);
	if (reached_collectibles != total_collectibles)
	{
		ft_printf("Error: Not all collectibles are reachable.\n");
		free_copy(copy, game->map_height);
		return (0);
	}

	// Vérification de la sortie
	ft_printf("Validating exit...\n");
	for (int y = 0; y < game->map_height; y++)
		ft_memcpy(copy[y], game->map[y], game->map_width);
	data.target = 'E';
	exit_reachable = flood_fill(&data, player_x, player_y);
	ft_printf("Exit reachable: %d\n", exit_reachable);
	if (!exit_reachable)
	{
		ft_printf("Error: Exit is not reachable after collecting all collectibles.\n");
		free_copy(copy, game->map_height);
		return (0);
	}

	// Libération et validation réussie
	free_copy(copy, game->map_height);
	ft_printf("Map is playable.\n");
	return (1);
}






