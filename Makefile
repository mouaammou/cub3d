# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:34:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/24 16:24:10 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc main.c MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/mouaammo/.brew/opt/glfw/lib/"

# FLAGS 			= -Wall -Wextra -Werror
NAME 			= cub3d
CC				= cc -O3  -g -fsanitize=address
RM				= rm -fr
MLX				= -lmlx -framework OpenGL -framework AppKit
LIBFT			= $(addprefix libft/, ft_atoi.c ft_putstr_fd.c ft_split.c ft_strcmp.c ft_strlen.c ft_substr.c is_white_space.c)
GNL				= $(addprefix get_next_line/, get_next_line_utils.c get_next_line.c)
PARSING		= $(addprefix parsing/, parsing.c free_2d_tab.c)
FILES			= main.c $(addprefix sources/, map.c player.c raycasting.c normalize_angle.c render_3d.c) $(LIBFT) $(PARSING) $(GNL)
HEADER_FILES	= $(addprefix include/, cub3d.h)
OBJECT_FILES	= $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(HEADER_FILES) $(OBJECT_FILES)
	@$(CC) $(FLAGS) $(MLX) $(OBJECT_FILES) -o $(NAME)
	@echo  $(NAME) "Created"

%.o:%.c $(HEADER_FILES)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJECT_FILES)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
.PHONY: all fclean clean re
