# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/03/02 17:03:39 by mleclair         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME 	= 	42sh

# Compilation
CC		= 	cc
CFLAGS	= 	-Wall -Wextra -Werror

# Directories
OBJDIR	= 	objs
LIBDIR	= 	./libft/

# Files && Objs
FILES 	=						\
			aperture 			\
			autocomplete 		\
			bquote 				\
			builtins 			\
			builtins2 			\
			builtin_job_control \
			cmd_env 			\
			cmd 				\
			double_array_sort 	\
			env_mod 			\
			error 				\
			fork 				\
			free 				\
			ft_cmpspec 			\
			ft_dollar 			\
			ft_strsplitquote 	\
			get_next_line 		\
			job_control			\
			main				\
			operator 			\
			redirection 		\
			set_env 			\
			subshell			\
			termcaps/history 	\
			termcaps/test 		\
			tilde 				\
			verif_quote 		\

OBJS  := 	$(addsuffix .o, $(FILES))

# **************************************************************************** #

# Bonus

.PHONY:		clean

# **************************************************************************** #

# Rules

all: 		$(NAME)

$(NAME): 	$(OBJS)
			@echo "----------------------------------------"
			@echo "|       Debut de la compilation        |"
			@echo "|              Ecole 42                |"
			@echo "|              minishell               |"
			@echo "|           sub compilation :          |"
			@echo "|                libft                 |"
			@make -C $(LIBDIR)
			@$(CC) $(CFLAGS) -o $@ $^ -L./libft/ -lft -lncurses -I. -I./termcaps
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

$(OBJS): 	%.o: %.c
			@$(CC) $(CFLAGS) -c -g  $< -o $@

clean:
			@rm -rf $(OBJS)
			@make -C $(LIBDIR) clean
fclean: 	clean
			@rm -rf $(NAME)
			@make -C $(LIBDIR) fclean

re: 		fclean all
			@make -C $(LIBDIR) re

# **************************************************************************** #
