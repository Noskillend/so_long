# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jco <jco@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 16:21:34 by jco               #+#    #+#              #
#    Updated: 2024/06/12 16:19:50 by jco              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_LIBC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRC_PRINTF = ft_printf.c ft_printchar.c ft_putnbr.c ft_putnbr_unsigned.c

SRC_GNL = get_next_line.c get_next_line_utils.c get_next_line_bonus.c

SRC_ALL = ${SRC_LIBC} ${SRC_BONUS} ${SRC_PRINTF} ${SRC_GNL}

OBJS_LIBC = ${SRC_LIBC:.c=.o}

OBJS_BONUS = ${SRC_BONUS:.c=.o}

OBJS_PRINTF = $(SRC_PRINTF:.c=.o)

OBJS_GNL = $(SRC_GNL:.c=.o)

OBJS_ALL = ${SRC_ALL:.c=.o}

FLAGS = -Wall -Werror -Wextra

CC = cc

HEADER = libft.h

all : $(NAME)

$(NAME): $(OBJS_LIBC) $(OBJS_PRINTF)  $(OBJS_GNL) $(OBJS_BONUS)
	ar -rcs $(NAME) $(OBJS_ALL)
	
%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

bonus : ${OBJS_BONUS}
	ar -rcs $(NAME) ${OBJS_BONUS}

clean :
	rm -rf $(OBJS_ALL)

fclean : clean
	rm -rf $(NAME)

re : fclean all

so:
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRC_ALL)
	gcc -nostartfiles -shared -o libft.so $(OBJS_ALL)