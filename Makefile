# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jco <jco@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 11:16:51 by jco               #+#    #+#              #
#    Updated: 2024/11/25 18:43:26 by jco              ###   ########.fr        #
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
SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/map.c \
       $(SRCS_DIR)/init.c \
       $(SRCS_DIR)/free.c \
       $(SRCS_DIR)/check_element_map.c \
       $(SRCS_DIR)/check_elment_map2.c \
       $(SRCS_DIR)/render.c \
       $(SRCS_DIR)/mouvement.c \
       $(SRCS_DIR)/utils.c \
	   $(SRCS_DIR)/flood_fill.c \
	   $(SRCS_DIR)/so_long.c
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

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