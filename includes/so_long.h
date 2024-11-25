/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:31:38 by jco               #+#    #+#             */
/*   Updated: 2024/11/25 02:37:36 by noskillend       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h" // Si vous utilisez la libft
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <stdio.h>

# define TILE_SIZE 64
# define MAX_MAP_HEIGHT 100

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	void	*floor_img;
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*exit_img;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		player_count;
	int		exit_count;
	void	*player_img_up;
	void	*player_img_down;
	void	*player_img_left;
	void	*player_img_right;
	void	*current_player_img;
	int		steps;

}	t_game;

typedef struct s_flood
{
	char	target;
	char	**map;
	int		width;
	int		height;
}	t_flood;

int		init_game(t_game *game, const char *map_path);
int		load_player_textures(t_game *game);
int		load_static_textures(t_game *game);
int		load_textures(t_game *game);
void	destroy_textures(t_game *game);
int		validate_player_position(t_game *game, char **copy);
void	render_map(t_game *game);
char	**allocate_map(int lines);
int		open_file(const char *path);
char	*read_and_trim_line(int fd);
int		fil_map(char **map, int fd, int lines);
char	**load_map(const char *map_path, int *width, int *height);
void	destroy_map(char **map);
void	destroy_game(t_game *game);
int 	validate_player_position(t_game *game, char **copy);
int		validate_map(t_game *game);
int		check_valid_characters(t_game *game);
int		check_rectangular(t_game *game);
int		check_surrounded_by_walls(t_game *game);
int		count_elements(t_game *game, int x, int y);
int		check_required_elements(t_game *game);
int		count_lines(const char *path);
int		can_reach_exit_after_collecting(char **map, int x, int y, t_game *game);
int		count_remaining_elements(char **map, int height, int width, char element);
int		is_map_playable(t_game *game);
int		is_valid_extension(const char *filename, const char *ext);
void	setup_player_position(t_game *game);
void	move_player(t_game *game, int x, int y, char direction);
int		handle_keypress(int keycode, t_game *game);
int		count_collectibles(char **map, int height, int width);

int		validate_map_and_extension(t_game *game, const char *map_path);
int		initialize_images(t_game *game, int *width, int *height);
int		initialize_window_and_images(t_game *game);

int		flood_fill(t_flood *data, int x, int y);
int		check_no_empty_lines(t_game *game);
char	**duplicate_map(t_game *game);
void	free_copy(char **copy, int rows);
#endif

