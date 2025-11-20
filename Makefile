# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faikhan <faikhan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/20 23:54:19 by faikhan           #+#    #+#              #
#    Updated: 2025/11/20 23:54:21 by faikhan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I minilibx
LDFLAGS = -L minilibx -lmlx -lX11 -lXext -lm

SRCS = main_min.c renderer.c movement.c init.c
OBJS = $(SRCS:.c=.o)

NAME = minimal_cub3d

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
