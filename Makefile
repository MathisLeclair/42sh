# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mleclair <mleclair@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 19:21:21 by mleclair          #+#    #+#              #
#    Updated: 2017/05/17 19:30:08 by aridolfi         ###   ########.fr        #
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

FILES 	=							\
			alias					\
			aperture				\
			autocomplete			\
			autocomplete2			\
			autocomplete3			\
			autocomplete4			\
			bquote					\
			builtins				\
			builtin_alias			\
			builtins4				\
			builtins2				\
			cmd_env					\
			cmd						\
			double_array_sort 		\
			is_file					\
			handle_chellrc			\
			env_mod					\
			error					\
			fork					\
			free					\
			ft_cmpspec				\
			ft_dollar				\
			ft_strsplitquote		\
			exec_condition			\
			get_next_line			\
			main					\
			operator				\
			redirection				\
			redirection_adv			\
			redirection_fd			\
			set_env					\
			subshell				\
			subshell2				\
			$(TCAPS)/test			\
			tilde					\
			verif_quote				\
			handle_argv				\
			handle_file				\
			bquote2					\
			history					\
			auto_prop				\
			builtins3				\
			builtin_history			\
			pipe					\
			signal					\
			getpwd					\
			reco_cmd				\
			bs_eol					\
			cmd2					\
			cmd3					\
			condition				\
			condition2				\
			hijack_prompt			\
			$(TCAPS)/arrow			\
			$(TCAPS)/copy_paste		\
			$(TCAPS)/ctrl_r			\
			$(TCAPS)/del_backspace	\
			$(TCAPS)/home_end		\
			$(TCAPS)/sel_desel		\
			$(TCAPS)/shift_arrow	\
			$(TCAPS)/utils			\
			$(TCAPS)/tab			\
			$(TCAPS)/touch			\
			$(TCAPS)/touch2			\
			$(TCAPS)/exclam

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

.PHONY			:	clean fclean

# **************************************************************************** #

# RULES

# Main rules
all				: 	$(OBJDIR) $(NAME)

re				: 	fclean all

# Compilation rules
$(OBJDIR)		:
					@mkdir -p $(OBJDIR) 2>&-
					@cd $(OBJDIR) && mkdir -p $(TCAPS) 2>&-

$(NAME)			: 	$(OBJP)
					@echo "-------------------------------------------------------------"
					@echo "|                  Debut de la compilation                  |"
					@echo "|                         Ecole 42                          |"
					@echo "|                           42sh                            |"
					@echo "|                     sub compilation :                     |"
					@echo "|                           libft                           |"
					@make -C $(LIBDIR)
					@$(CC) $(CFLAGS) -o $@ $^ -L$(LIBDIR) -lft -lncurses -I. -I./$(TCAPS) -I$HOME/.brew/include
					@echo "|                        CAKE DONE !                        |"
					@echo "-------------------------------------------------------------"
					@cat cake-v2.ascii
					@echo ""
					@echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"

$(OBJDIR)/%.o	:	%.c
					@$(CC) $(CFLAGS) -c -g  $< -o $@

# Clean rules
clean			:
					@rm -rf $(OBJDIR)
					@make clean -C $(LIBDIR)

fclean			: 	clean
					@rm -f $(NAME)
					@make fclean -C $(LIBDIR)

# **************************************************************************** #
