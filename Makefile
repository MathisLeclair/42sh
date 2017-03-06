# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/03/06 12:33:04 by aridolfi         ###   ########.fr        #
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
TCAPS	=	termcaps
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
			redirection_adv		\
			redirection_fd		\
			set_env 			\
			subshell			\
			$(TCAPS)/test 		\
			tilde 				\
			verif_quote 		\
			handle_argv 		\
			handle_file			\
			history				\
			auto_prop

OBJ  := 	$(addsuffix .o, $(FILES))

# Paths foreach
OBJP =		$(addprefix $(OBJDIR)/, $(OBJ))

# **************************************************************************** #

# SPECIAL CHARS

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

# Rules

all: 		$(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR) 2>&-
	@cd $(OBJDIR) && mkdir -p $(TCAPS) 2>&-

$(NAME): 	$(OBJP)
			@echo "----------------------------------------"
			@echo "|       Debut de la compilation        |"
			@echo "|              Ecole 42                |"
			@echo "|              minishell               |"
			@echo "|           sub compilation :          |"
			@echo "|                libft                 |"
			@make -C $(LIBDIR)
			@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) -lft -lncurses -I. -I./$(TCAPS)
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

$(OBJDIR)/%.o:	%.c
			@$(CC) $(CFLAGS) -c -g  $< -o $@

clean:
			@rm -rf $(OBJDIR)
			@make clean -C $(LIBDIR)

fclean: 	clean
			@rm -f $(NAME)
			@make fclean -C $(LIBDIR)

re: 		fclean all

# **************************************************************************** #
