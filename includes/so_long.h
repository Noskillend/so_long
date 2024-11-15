/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jco <jco@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:31:38 by jco               #+#    #+#             */
/*   Updated: 2024/11/15 11:36:51 by jco              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*texture[5];
	t_map	*map;
}	t_data;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;
#endif