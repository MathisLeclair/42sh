# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/02/28 12:45:41 by mleclair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = 42sh

# FILE & OBJ =

PATHTOMAKEFILE = ./libft/

FILE =	main \
		cmd \
		error \
		ft_cmpspec \
		env_mod \
		get_next_line \
		cmd_env \
		ft_dollar \
		set_env \
		fork \
		ft_strsplitquote \
		free \
		builtins \
		builtins2 \
		aperture \
		tilde \
		verif_quote \
		double_array_sort \
		autocomplete \
		termcaps/test \
		termcaps/history \
		redirection \
		operator \
		bquote \
		subshell

OBJ  := $(addsuffix .o, $(FILE))

# **************************************************************************** #

# Rules

all: $(NAME)

$(NAME): $(OBJ)
	@echo "----------------------------------------"
	@echo "|       Debut de la compilation        |"
	@echo "|              Ecole 42                |"
	@echo "|              minishell               |"
	@echo "|           sub compilation :          |"
	@echo "|                libft                 |"
	@make -C $(PATHTOMAKEFILE)
	@gcc -Wall -Werror -L./libft/ -lft -o $(NAME) -Wextra $(OBJ) -lncurses -I. -I./termcaps
	@echo "|                 FIN                  |"
	@echo "----------------------------------------"
	@echo "               ________"
	@echo "          _,.-Y  |  |  Y-._"
	@echo "      .-~\"   ||  |  |  |   \"-."
	@echo "      I\" \"\"==\"|\" !\"\"! \"|\"[]\"\"|     _____"
	@echo "      L__  [] |..------|:   _[----I\" .-{\"-."
	@echo "     I___|  ..| l______|l_ [__L]_[I_/r(=}=-P"
	@echo "    [L______L_[________]______j~  '-=c_]/=-^"
	@echo "     \_I_j.--.\==I|I==_/.--L_]"
	@echo "       [_((==)[\`-----\"](==)j"
	@echo "          I--I\"~~\"\"\"~~\"I--I"
	@echo "          |[]|         |[]|"
	@echo "          l__j         l__j"
	@echo "          |!!|         |!!|"
	@echo "          |..|         |..|"
	@echo "          ([])         ([])"
	@echo "          ]--[         ]--["
	@echo "          [_L]         [_L]"
	@echo "         /|..|\       /|..|\\"
	@echo "        \`=}--{='     \`=}--{=i'"
	@echo "       .-^--r-^-.   .-^--r-^-."
	@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

$(OBJ): %.o: %.c
	@gcc -c -Wall -Wextra -Werror -g  $< -o $@

clean:
	@rm -rf $(OBJ)
	@make -C $(PATHTOMAKEFILE) clean
fclean: clean
	@rm -rf $(NAME)
	@make -C $(PATHTOMAKEFILE) fclean

re: fclean all
	@make -C $(PATHTOMAKEFILE) re

# **************************************************************************** #

.PHONY : all clean fclean re
