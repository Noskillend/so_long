# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jco <jco@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/15 11:16:51 by jco               #+#    #+#              #
#    Updated: 2024/11/15 11:21:23 by jco              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g3

# Detect the OS
UNAME_S := $(shell uname -s)

# Set platform-specific variables
ifeq ($(UNAME_S), Linux)
    MLX_DIR = ./minilibx-linux
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
    LIBS = -lX11 -lXext -lm -lbsd
endif

ifeq ($(UNAME_S), Darwin)
    MLX_DIR = ./minilibx-mac
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
    LIBS = -framework OpenGL -framework AppKit
endif

ifeq ($(OS), Windows_NT)
    MLX_DIR = ./minilibx-windows
    MLX = $(MLX_DIR)/libmlx.a
    MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
    LIBS = -lX11 -lXext -lm -lbsd
endif

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
    $(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX):
    make -C $(MLX_DIR)

clean:
    rm -f $(OBJS)
    make clean -C $(MLX_DIR)

fclean: clean
    rm -f $(NAME)
    make fclean -C $(MLX_DIR)

re: fclean all