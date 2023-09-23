# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 12:34:07 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/23 12:57:13 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# gcc main.c MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/mouaammo/.brew/opt/glfw/lib/"

# FLAGS 			= -Wall -Wextra -Werror
NAME 			= cub3d
CC				= cc  -Ofast -g #-fsanitize=address
RM				= rm -fr
MLX				= -lmlx -framework OpenGL -framework AppKit
LIBFT_FILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_strlen.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
			ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_itoa.c ft_split.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_isprint.c \
			ft_putnbr_fd.c ft_strtrim.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_memcmp.c ft_memchr.c ft_bzero.c ft_calloc.c ft_striteri.c ft_strmapi.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

FILES			= main.c $(addprefix sources/, map.c player.c raycasting.c normalize_angle.c render_3d.c)
HEADER_FILES	= $(addprefix include/, cub3d.h) libft/libft.h
OBJECT_FILES	= $(FILES:.c=.o)

all: $(NAME)

$(NAME): lib $(HEADER_FILES) $(OBJECT_FILES)
	@$(CC) $(FLAGS) libft/libft.a $(MLX) $(OBJECT_FILES) -o $(NAME)
	@echo "CC " $(NAME)

lib:
	@$(MAKE) -C libft
	@$(MAKE) bonus -C libft

%.o:%.c lib $(HEADER_FILES) $(LIBFT_FILES)
	$(CC) $(FLAGS) libft/libft.a  -c $< -o $@

clean:
	@$(MAKE) clean -C libft
	$(RM) $(OBJECT_FILES)

fclean: clean
	@$(MAKE) fclean -C libft
	$(RM) $(NAME)

re: fclean all
.PHONY: all fclean clean re
