# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:34:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/29 15:48:08 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS 			= -Wall -Wextra -Werror
NAME 			= cub3d
CC				= cc -Ofast
RM				= rm -fr
MLX				= -lmlx -framework OpenGL -framework AppKit
LIBFT			= $(addprefix libft/, ft_atoi.c ft_putstr_fd.c ft_split.c ft_strcmp.c ft_strlen.c ft_substr.c is_white_space.c ft_strtrim.c)
GNL				= $(addprefix get_next_line/, get_next_line_utils.c get_next_line.c)
PARSING			= $(addprefix parsing/, parsing.c parsing1.c parsing2.c parsing3.c parsing4.c  parsing5.c free_2d_tab.c tools.c)
FILES			= $(addprefix sources/, minimap.c textures_data.c what_direction.c draw.c horz_vert_inter.c \
						ray_angle.c map.c player.c raycasting.c normalize_angle.c render_3d.c) $(LIBFT) $(PARSING) $(GNL)

HEADER_FILES	= $(addprefix include/, cub3d.h)

MANDATORY_FILES	= $(FILES) main.c
OBJECT_FILES	= $(MANDATORY_FILES:.c=.o)
BONUS_FILES		= $(FILES) main_bonus.c
F_OBJECT_FILES	= $(BONUS_FILES:.c=.o)

all: $(NAME)

$(NAME): $(HEADER_FILES) $(OBJECT_FILES)
	@$(CC) $(FLAGS) $(MLX) $(OBJECT_FILES) -o $(NAME)
	@printf "\n\033[1;36m ───────────── Done ──────────── \033[0m\n\n"

%.o:%.c $(HEADER_FILES) Makefile
	@$(CC) $(FLAGS) -c $< -o $@
	@printf "\033[1;36m Compiling \033[0m $< \033[1;36m√\033[0m\n"
clean:
	@$(RM) $(OBJECT_FILES) $(F_OBJECT_FILES)

fclean: clean
	@$(RM) $(NAME)

bonus: $(HEADER_FILES) $(F_OBJECT_FILES)
	@$(CC) $(FLAGS) $(MLX) $(F_OBJECT_FILES) -o $(NAME)
	@printf "\n\033[1;36m ─────────────Bonus Done ──────────── \033[0m\n\n"

re: fclean all
.PHONY: all fclean clean re bonus
