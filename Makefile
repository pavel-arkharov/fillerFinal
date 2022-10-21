# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parkharo <parkharo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/14 18:13:21 by parkharo          #+#    #+#              #
#    Updated: 2022/10/21 18:14:29 by parkharo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parkharo.filler

FLAGS = -Wall -Werror -Wextra
INCLUDES = -I ./includes

SRC_PATH = src/
OBJ_PATH = obj/
LIBFT_PATH = ft_printf/

SRCS_NAME = main.c \
	init.c \
	play.c \
	utils.c \
	piece.c \
	utils2.c

SRCS = $(addprefix $(SRC_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	gcc $(FLAGS) $(OBJ) $(INCLUDES) -L $(LIBFT_PATH) -lftprintf -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p `dirname $@`
	gcc -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	make -C $(LIBFT_PATH) fclean
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re