/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:38:09 by jco               #+#    #+#             */
/*   Updated: 2024/11/20 13:07:49 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "../includes/so_long.h"


void init_struct(t_game *game)
{
    if (!game)
        return;

    game->mlx = NULL;
    game->win = NULL;
    game->map = NULL;
    game->map_width = 0;
    game->map_height = 0;
    game->floor_img = NULL;
    game->wall_img = NULL;
    game->player_img = NULL;
    game->collectible_img = NULL;
    game->exit_img = NULL;
    game->player_x = 0;
    game->player_y = 0;
    game->collectibles = 0;
    game->player_count = 0;
    game->exit_count = 0;
    game->player_img_up = NULL;
    game->player_img_down = NULL;
    game->player_img_left = NULL;
    game->player_img_right = NULL;
    game->current_player_img = NULL;
    game->steps = 0;
}


int	init_game(t_game *game, const char *map_path)
{
	int	width;
	int	height;
	
	init_struct(game);

	game->map = load_map(map_path, &game->map_width, &game->map_height);
	if (!game->map)
		return (0);
	if (!is_valid_extension(map_path, ".ber"))
		return (0);
if (!validate_map(game))
{
	ft_printf("Error: Map validation failed.\n");
	return (0);
}
	game->steps = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,game->map_height * TILE_SIZE, "so_long");
	game->floor_img = mlx_xpm_file_to_image(game->mlx, "textures/sol.xpm", &width, &height);
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/bush.xpm", &width, &height);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/perso_down.xpm", &width, &height);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx, "textures/collectible.xpm", &width, &height);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &width, &height);
	game->player_img_up = mlx_xpm_file_to_image(game->mlx, "textures/perso_back.xpm", &width, &height);
	game->player_img_down = mlx_xpm_file_to_image(game->mlx, "textures/perso_down.xpm", &width, &height);
	game->player_img_left = mlx_xpm_file_to_image(game->mlx, "textures/perso_left.xpm", &width, &height);
	game->player_img_right = mlx_xpm_file_to_image(game->mlx, "textures/perso_right.xpm", &width, &height);
	game->current_player_img = game->player_img_down; // Position initiale

	if (!game->floor_img || !game->wall_img || !game->player_img
		|| !game->collectible_img || !game->exit_img)
	{
		destroy_game(game);
		return (0);
	}
	return (1);
}

void destroy_game(t_game *game)
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
		mlx_destroy_display(game->mlx); // Libère les ressources système MLX
		free(game->mlx);
	}
	destroy_map(game->map); // Libère la carte
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

int is_map_playable(t_game *game)
{
    char **copy;
    int player_x = -1;
    int player_y = -1;
    int y;

    copy = malloc(sizeof(char *) * (game->map_height + 1));
    if (!copy)
        return (0);

    // Duplication de la map
    for (y = 0; y < game->map_height; y++)
    {
        copy[y] = ft_strdup(game->map[y]);
        if (!copy[y]) // Si l'allocation échoue, libérer ce qui est déjà alloué
        {
            free_copy(copy, y);
            return (0);
        }
    }
    copy[y] = NULL;

    // Recherche de la position du joueur
    for (y = 0; y < game->map_height; y++)
    {
        for (int x = 0; x < game->map_width; x++)
        {
            if (game->map[y][x] == 'P')
            {
                player_x = x;
                player_y = y;
                break;
            }
        }
    }
    if (player_x == -1 || player_y == -1)
    {
        ft_printf("Error: Player position not found.\n");
        free_copy(copy, game->map_height);
        return (0);
    }

    // Validation des collectibles
    int collectibles_count = count_remaining_elements(game->map, game->map_height, game->map_width, 'C');
    int reached_collectibles = flood_fill(copy, player_x, player_y, game, 'C');
    if (reached_collectibles != collectibles_count)
    {
        ft_printf("Error: Not all collectibles are reachable.\n");
        free_copy(copy, game->map_height);
        return (0);
    }

    // Revalidation pour l'accès à la sortie
    for (y = 0; y < game->map_height; y++)
        ft_memcpy(copy[y], game->map[y], game->map_width);

    int exit_reachable = flood_fill(copy, player_x, player_y, game, 'E');
    if (exit_reachable == 0)
    {
        ft_printf("Error: Exit is not reachable after collecting all collectibles.\n");
        free_copy(copy, game->map_height);
        return (0);
    }

    // Nettoyage final
    free_copy(copy, game->map_height);
    return (1);
}



