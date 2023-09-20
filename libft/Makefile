# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouaammo <mouaammo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 03:42:10 by mouaammo          #+#    #+#              #
#    Updated: 2023/09/20 03:42:24 by mouaammo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -f
AR = ar -crs
FLAGS = -Wall -Werror -Wextra
NAME = libft.a

FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_strlen \
	ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
	ft_strnstr ft_strlcpy ft_strlcat ft_atoi ft_strdup \
	ft_substr ft_strjoin ft_itoa ft_split \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_isprint \
	ft_putnbr_fd ft_strtrim ft_memcpy ft_memmove ft_memset \
	ft_memcmp ft_memchr ft_bzero ft_calloc ft_striteri ft_strmapi


BFILES = ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
	ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

OBJ=$(FILES:=.o)
BOBJ=$(BFILES:=.o)

all: $(NAME)

bonus: $(BOBJ)
	@$(AR) $(NAME) $(BOBJ)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(NAME) is created"

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(BOBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
.PHONY: all fclean clean re bonus
