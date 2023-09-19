# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:34:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/19 11:26:47 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc main.c MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/mouaammo/.brew/opt/glfw/lib/"

# FLAGS 			= -Wall -Wextra -Werror
NAME 			= cub3d
CC				= cc -g -fsanitize=address
RM				= rm -fr
MLX				= -lmlx -framework OpenGL -framework AppKit

FILES			= main.c $(addprefix sources/, map.c player.c test_ray.c)
HEADER_FILES	= $(addprefix include/, cub3d.h)
OBJECT_FILES	= $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT_FILES)
	@$(CC) $(FLAGS) $(MLX) $(OBJECT_FILES) -o $(NAME)
	@echo "CC " $(NAME)

%.o:%.c $(HEADER_FILES)
	$(CC) $(FLAGS)  -c $< -o $@

clean:
	$(RM) $(OBJECT_FILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all
.PHONY: all fclean clean re
