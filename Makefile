# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:34:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/14 17:07:28 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS 			= -Wall -Wextra -Werror
NAME 			= cub3d
CC				= cc
RM				= rm -fr
MLX				= -lmlx -framework OpenGL -framework AppKit

FILES			= main.c $(addprefix sources/, map.c player.c ray.c)
HEADER_FILES	= $(addprefix include/, cub3d)
OBJECT_FILES	= $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	@$(CC) $(FLAGS) $(MLX) $(OBJECT_FILES) -o $(NAME)
	@echo "CC " $(NAME)

%.o:%.cpp $(HEADER_FILES)
	$(CC) $(FLAGS)  -c $< -o $@

clean:
	$(RM) $(OBJECT_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all fclean clean re
