# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfrochot <bfrochot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/03/17 17:32:09 by bfrochot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PATH = ./sprintf/

FILE =	free_swap \
		ft_atoi \
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
		ft_strfind	\
		ft_striter \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlen \
		ft_strmap \
		ft_strmapi \
		ft_strcfind \
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
		ft_strjoinfree \
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
		$(PATH)sptf_array_ptr \
		ft_remstr \
		ft_strcdup \
		ft_power \
		bs_str

OBJ  := $(addsuffix .o, $(FILE))

# **************************************************************************** #

LOG_CLEAR		= \033[2K
LOG_UP			= \033[A
LOG_NOCOLOR		= \033[0m
LOG_BOLD		= \033[1m
LOG_UNDERLINE	= \033[4m
LOG_BLINKING	= \033[5m
LOG_BLACK		= \033[1;30m
LOG_RED			= \033[1;31m
LOG_GREEN		= \033[1;32m
LOG_YELLOW		= \033[1;33m
LOG_BLUE		= \033[1;34m
LOG_VIOLET		= \033[1;35m
LOG_CYAN		= \033[1;36m
LOG_WHITE		= \033[1;37m

# Bonus

.PHONY:		clean fclean

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "--$(LOG_CLEAR)$(LOG_RED)$(NAME)$(LOG_NOCOLOR) ....................................... $(LOG_RED)Cake Done$(LOG_NOCOLOR)$(LOG_UP)"

%.o: %.c
	@echo "--$(LOG_CLEAR)$(LOG_RED)$(NAME)$(LOG_NOCOLOR) ....................................... $(LOG_RED)$<$(LOG_NOCOLOR)$(LOG_UP)"
	@gcc -c -Wall -Wextra -g -Werror $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
