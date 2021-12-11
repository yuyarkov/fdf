# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirony <dirony@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 20:08:26 by dirony            #+#    #+#              #
#    Updated: 2021/12/11 15:26:59 by dirony           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

HEADER = fdf.h

SRC = 		main.c			number_utils.c\
			string_utils.c	parse_utils.c\
			draw_utils.c	rotation_utils.c\
			iso_utils.c		keycode_utils.c\
			flat_utils.c

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Werror -Wextra

COMPILE = gcc $(CFLAGS)

REMOVE = rm -f

%.o 	:	%.c	$(HEADER)
			$(COMPILE) -Imlx -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@$(COMPILE) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@$(REMOVE) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(REMOVE) $(NAME)

re: fclean all
