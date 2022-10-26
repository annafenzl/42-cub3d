# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afenzl <afenzl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 14:36:07 by afenzl            #+#    #+#              #
#    Updated: 2022/10/26 14:53:26 by afenzl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM := rm -f

LIBS = ./libft/libs.a
MLX = ./MLX/libmlx.a

SRC = 	./src/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./MLX/
	make -C ./libft/
	$(CC) $(CFLAGS) $(MLX) $(LIBS) $(OBJ) -framework OpenGL -framework AppKit -Imlx -o $(NAME)

clean:
	make fclean -C ./libft
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
