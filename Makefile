# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noskillend <noskillend@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 11:16:51 by jco               #+#    #+#              #
#    Updated: 2024/11/16 01:52:07 by noskillend       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom de l'exécutable
NAME = so_long

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

# Répertoires
SRCS_DIR = src
OBJS_DIR = obj
MLX_DIR = minilibx
LIBFT_DIR = libft

# Sources et objets
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# Bibliothèques
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

# Options pour MiniLibX sous Linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd

# Commandes de Make
all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -I$(LIBFT_DIR) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(LIBFT_DIR) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all