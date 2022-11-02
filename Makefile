# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/23 14:36:07 by afenzl            #+#    #+#              #
#    Updated: 2022/11/01 17:43:46 by dhamdiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
LIBMLX	:= ./MLX42
LIBFT	:= ./libft

GLFW_LIB = /Users/$(USER)/goinfre/.brew/opt/glfw/lib
GLFW_INC = /Users/$(USER)/goinfre/.brew/opt/glfw/include
HEADERS	:= -I./include -I$(LIBMLX)/include -I$(GLFW_INC)
LIBS	:= $(LIBMLX)/libmlx42.a -ldl -lglfw -pthread -lm -L$(GLFW_LIB) ./libft/libs.a
SRCS	:= ./src/main.c ./src/parse_get.c ./src/parse_set.c ./src/parse_check.c ./src/movement.c ./src/raycasting_cast.c ./src/raycasting_draw.c
OBJS	:= ${SRCS:.c=.o}

DEPS	:= ./inc/cub3d.h

all: libs $(NAME)

libs:
	@$(MAKE) -C $(LIBMLX)
	@$(MAKE) -C $(LIBFT)

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(DEPS) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBMLX) clean
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBMLX) fclean
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx