# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/01/13 15:05:07 by mleclair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PATH = ./sprintf/

FILE =	ft_atoi \
		ft_bzero \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_itoa \
		ft_lstadd \
		ft_lstdel \
		ft_lstdelone \
		ft_lstiter \
		ft_lstmap \
		ft_lstnew \
		ft_memalloc \
		ft_memccpy \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memdel \
		ft_memmove \
		ft_memset \
		ft_putchar \
		ft_atoi_base_pr \
		ft_putchar_fd \
		ft_putendl \
		ft_putendl_fd \
		ft_putnbr \
		ft_putnbr_fd \
		ft_putstr \
		ft_putstr_fd \
		ft_strcat \
		ft_strchr \
		ft_strclr \
		ft_strcmp \
		ft_strcpy \
		ft_strdel \
		ft_strdup \
		ft_strequ \
		ft_striter \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlen \
		ft_strmap \
		ft_strmapi \
		ft_strncat \
		ft_strncmp \
		ft_strncpy \
		ft_strnequ \
		ft_strnew \
		ft_strnstr \
		ft_strrchr \
		ft_strsplit \
		ft_strstr \
		ft_strsub \
		ft_strtrim \
		ft_tolower \
		ft_toupper \
		ft_itoa_base \
		addprint \
		diese \
		ft_atoi_base \
		conv \
		ft_isokay \
		ft_opts \
		part1 \
		part2 \
		part3 \
		printf \
		tableaupointeursurfonction \
		opts1 \
		opts2 \
		$(PATH)ft_satoi_base\
		$(PATH)ft_sisokay \
		$(PATH)ft_sopts \
		$(PATH)saddprint \
		$(PATH)sconv \
		$(PATH)sdiese \
		$(PATH)sopts1 \
		$(PATH)sopts2 \
		$(PATH)spart1 \
		$(PATH)spart2 \
		$(PATH)spart3 \
		$(PATH)sprintf \
		$(PATH)stableaupointeursurfonction

OBJ  := $(addsuffix .o, $(FILE))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)


$(OBJ): %.o: %.c
	@gcc -c -Wall -Wextra -g -Werror $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
